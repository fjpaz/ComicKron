/***************************************************************************
 *   Copyright (C) 2006 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   In addition, as a special exception, the copyright holders give       *
 *   permission to link the code of portions of this program with the      *
 *   OpenSSL library under certain conditions as described in each         *
 *   individual source file, and distribute linked combinations            *
 *   including the two.                                                    *
 *   You must obey the GNU General Public License in all respects          *
 *   for all of the code used other than OpenSSL.  If you modify           *
 *   file(s) with this exception, you may extend this exception to your    *
 *   version of the file(s), but you are not obligated to do so.  If you   *
 *   do not wish to do so, delete this exception statement from your       *
 *   version.  If you delete this exception statement from all source      *
 *   files in the program, then also delete it here.                       * 
 ***************************************************************************/

#if defined(_MSC_VER)  &&  _MSC_VER <= 1200
#pragma warning(disable: 4786)
#endif

#include <algorithm>
#include <deque>
#include <iostream>

#include "PdfMemDocument.h"

#include "base/PdfDefinesPrivate.h"

#include "base/PdfArray.h"
#include "base/PdfDictionary.h"
#include "base/PdfObject.h"
#include "base/PdfParserObject.h"
#include "base/PdfStream.h"
#include "base/PdfVecObjects.h"

#include "PdfDestination.h"
#include "PdfInfo.h"
#include "PdfNamesTree.h"
#include "PdfOutlines.h"
#include "PdfPage.h"
#include "PdfPagesTree.h"

using namespace std;

namespace PoDoFo {

PdfMemDocument::PdfMemDocument()
    : PdfDocument(), m_pEncrypt( NULL ), m_pParser( NULL )
{
    m_eVersion    = ePdfVersion_Default;
    m_bLinearized = false;
}

PdfMemDocument::PdfMemDocument(bool bOnlyTrailer)
    : PdfDocument(bOnlyTrailer), m_pEncrypt( NULL ), m_pParser( NULL )
{
    m_eVersion    = ePdfVersion_Default;
    m_bLinearized = false;
}

void PdfMemDocument::InitFromParser( PdfParser* pParser )
{
    m_eVersion     = pParser->GetPdfVersion();
    m_bLinearized  = pParser->IsLinearized();

    PdfObject* pTrailer = new PdfObject( *(pParser->GetTrailer()) );
    this->SetTrailer ( pTrailer ); // Set immediately as trailer
                                   // so that pTrailer has an owner
                                   // and GetIndirectKey will work

    PdfObject* pCatalog = pTrailer->GetIndirectKey( "Root" );
    if( !pCatalog )
    {
        PODOFO_RAISE_ERROR_INFO( ePdfError_NoObject, "Catalog object not found!" );
    }


    PdfObject* pInfo = pTrailer->GetIndirectKey( "Info" );
    PdfInfo*   pInfoObj;
    if( !pInfo )
    {
        pInfoObj = new PdfInfo( PdfDocument::GetObjects() );
        pTrailer->GetDictionary().AddKey( "Info", pInfoObj->GetObject()->Reference() );
    }
    else
        pInfoObj = new PdfInfo( pInfo );

    if( pParser->GetEncrypted() )
    {
        // All PdfParserObjects have a pointer to the PdfEncrypt obkect
        // So we have to take ownership of it.
        delete m_pEncrypt;
        m_pEncrypt = pParser->TakeEncrypt();
    }

    this->SetCatalog ( pCatalog );
    this->SetInfo    ( pInfoObj );
}

PdfMemDocument::~PdfMemDocument()
{
    this->Clear();
}

void PdfMemDocument::Clear() 
{
    if( m_pEncrypt )
    {
        delete m_pEncrypt;
        m_pEncrypt = NULL;
    }

    if( m_pParser ) 
    {
        delete m_pParser;
        m_pParser = NULL;
    }

    PdfDocument::Clear();
}

void PdfMemDocument::Load( const char* pBuffer, long lLen )
{
    this->Clear();

    // Call parse file instead of using the constructor
    // so that m_pParser is initialized for encrypted documents
    m_pParser = new PdfParser( PdfDocument::GetObjects() );
    m_pParser->ParseFile( pBuffer, lLen, true );
    InitFromParser( m_pParser );
    InitPagesTree();

    // Delete the temporary pdfparser object.
    // It is only set to m_pParser so that SetPassword can work
    delete m_pParser;
    m_pParser = NULL;
}

void PdfMemDocument::Load( const PdfRefCountedInputDevice & rDevice )
{
    this->Clear();

    // Call parse file instead of using the constructor
    // so that m_pParser is initialized for encrypted documents
    m_pParser = new PdfParser( PdfDocument::GetObjects() );
    m_pParser->ParseFile( rDevice, true );
    InitFromParser( m_pParser );
    InitPagesTree();

    // Delete the temporary pdfparser object.
    // It is only set to m_pParser so that SetPassword can work
    delete m_pParser;
    m_pParser = NULL;
}

/** Checks whether the documents is tagged to imlpement a vendor-specific
 *  extension to the current PDF version.
 *  \param ns  namespace of the extension
 *  \param level  level of the extension
 */
bool PdfMemDocument::HasPdfExtension( const char* ns, pdf_int64 level ) const {
    
    PdfObject* pExtensions = this->GetCatalog()->GetIndirectKey("Extensions");
    
    if (pExtensions) {
        
        PdfObject* pExtension = pExtensions->GetIndirectKey(ns);
        
        if (pExtension) {
            
            PdfObject* pLevel = pExtension->GetIndirectKey("ExtensionLevel");
            
            if (pLevel && pLevel->IsNumber() && pLevel->GetNumber() == level)
                return true;
        }
    }
    
    return false;
}

/** Return the list of all vendor-specific extensions to the current PDF version.
 *  \param ns  namespace of the extension
 *  \param level  level of the extension
 */
std::vector<PdfExtension> PdfMemDocument::GetPdfExtensions() const {
    
    std::vector<PdfExtension> result;
    
    PdfObject* pExtensions = this->GetCatalog()->GetIndirectKey("Extensions");

    if (pExtensions) {

        // Loop through all declared extensions
        for (TKeyMap::const_iterator it = pExtensions->GetDictionary().GetKeys().begin(); it != pExtensions->GetDictionary().GetKeys().end(); ++it) {

            PdfObject *bv = it->second->GetIndirectKey("BaseVersion");
            PdfObject *el = it->second->GetIndirectKey("ExtensionLevel");
            
            if (bv && el && bv->IsName() && el->IsNumber()) {

                // Convert BaseVersion name to EPdfVersion
                for(int i=0; i<=MAX_PDF_VERSION_STRING_INDEX; i++) {
                    if(bv->GetName().GetName() == s_szPdfVersionNums[i]) {
                        result.push_back(PdfExtension(it->first.GetName().c_str(), static_cast<EPdfVersion>(i), el->GetNumber()));
                    }
                }
            }
        }
    }
    
    return result;
}
    
void PdfMemDocument::SetPassword( const std::string & sPassword )
{
    PODOFO_RAISE_LOGIC_IF( !m_pParser, "SetPassword called without reading a PDF file." );

    m_pParser->SetPassword( sPassword );
    InitFromParser( m_pParser );
    InitPagesTree();
}

void PdfMemDocument::FreeObjectMemory( const PdfReference & rRef, bool bForce )
{
    FreeObjectMemory( this->GetObjects().GetObject( rRef ), bForce );
}

void PdfMemDocument::FreeObjectMemory( PdfObject* pObj, bool bForce )
{
    if( !pObj ) 
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }
    
    PdfParserObject* pParserObject = dynamic_cast<PdfParserObject*>(pObj);
    if( !pParserObject ) 
    {
        PODOFO_RAISE_ERROR_INFO( ePdfError_InvalidHandle, 
                                 "FreeObjectMemory works only on classes of type PdfParserObject." );
    }

    pParserObject->FreeObjectMemory( bForce );
}

};

