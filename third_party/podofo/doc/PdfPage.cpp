/***************************************************************************
 *   Copyright (C) 2005 by Dominik Seichter                                *
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

#include "PdfPage.h" 

#include "base/PdfDefinesPrivate.h"

#include "base/PdfDictionary.h"
#include "base/PdfRect.h"
#include "base/PdfVariant.h"
#include "base/PdfStream.h"

#include "PdfDocument.h"

namespace PoDoFo {

PdfPage::PdfPage( const PdfRect & rSize, PdfDocument* pParent )
    : PdfElement( "Page", pParent ), PdfCanvas(), m_pContents( NULL )
{
    InitNewPage( rSize );
}

PdfPage::PdfPage( const PdfRect & rSize, PdfVecObjects* pParent )
    : PdfElement( "Page", pParent ), PdfCanvas(), m_pContents( NULL )
{
    InitNewPage( rSize );
}

PdfPage::PdfPage( PdfObject* pObject, const std::deque<PdfObject*> & rListOfParents )
    : PdfElement( "Page", pObject ), PdfCanvas()
{
    m_pResources = this->GetObject()->GetIndirectKey( "Resources" );
    if( !m_pResources ) 
    {
        // Resources might be inherited
        std::deque<PdfObject*>::const_reverse_iterator it = rListOfParents.rbegin();

        while( it != rListOfParents.rend() && !m_pResources )
        {
            m_pResources = (*it)->GetIndirectKey( "Resources" );
            ++it;
        }
    }

    PdfObject* pContents = this->GetObject()->GetIndirectKey( "Contents" );
    if (pContents)
    {
        m_pContents = new PdfContents( pContents );
    }
    else
    {
        // Create object on demand
        m_pContents =  NULL;
    }
}

PdfPage::~PdfPage()
{
    delete m_pContents;	// just clears the C++ object from memory, NOT the PdfObject
}

void PdfPage::InitNewPage( const PdfRect & rSize )
{
    PdfVariant mediabox;
    rSize.ToVariant( mediabox );
    this->GetObject()->GetDictionary().AddKey( "MediaBox", mediabox );

    // The PDF specification suggests that we send all available PDF Procedure sets
    this->GetObject()->GetDictionary().AddKey( "Resources", PdfObject( PdfDictionary() ) );

    m_pResources = this->GetObject()->GetIndirectKey( "Resources" );
    m_pResources->GetDictionary().AddKey( "ProcSet", PdfCanvas::GetProcSet() );
}

void PdfPage::CreateContents() 
{
    if( !m_pContents ) 
    {
        m_pContents = new PdfContents( this );
        this->GetObject()->GetDictionary().AddKey( PdfName::KeyContents, 
                                                   m_pContents->GetContents()->Reference());   
    }
}

PdfObject* PdfPage::GetContents() const 
{ 
    if( !m_pContents ) 
    {
        const_cast<PdfPage*>(this)->CreateContents();
    }

    return m_pContents->GetContents(); 
}

PdfObject* PdfPage::GetContentsForAppending() const
{ 
    if( !m_pContents ) 
    {
        const_cast<PdfPage*>(this)->CreateContents();
    }

    return m_pContents->GetContentsForAppending(); 
}

PdfRect PdfPage::CreateStandardPageSize( const EPdfPageSize ePageSize, bool bLandscape )
{
    PdfRect rect;

    switch( ePageSize ) 
    {
        case ePdfPageSize_A0:
            rect.SetWidth( 2384.0 );
            rect.SetHeight( 3370.0 );
            break;

        case ePdfPageSize_A1:
            rect.SetWidth( 1684.0 );
            rect.SetHeight( 2384.0 );
            break;

        case ePdfPageSize_A2:
            rect.SetWidth( 1191.0 );
            rect.SetHeight( 1684.0 );
            break;
            
        case ePdfPageSize_A3:
            rect.SetWidth( 842.0 );
            rect.SetHeight( 1190.0 );
            break;

        case ePdfPageSize_A4:
            rect.SetWidth( 595.0 );
            rect.SetHeight( 842.0 );
            break;

        case ePdfPageSize_A5:
            rect.SetWidth( 420.0 );
            rect.SetHeight( 595.0 );
            break;

        case ePdfPageSize_A6:
            rect.SetWidth( 297.0 );
            rect.SetHeight( 420.0 );
            break;

        case ePdfPageSize_Letter:
            rect.SetWidth( 612.0 );
            rect.SetHeight( 792.0 );
            break;
            
        case ePdfPageSize_Legal:
            rect.SetWidth( 612.0 );
            rect.SetHeight( 1008.0 );
            break;

        case ePdfPageSize_Tabloid:
            rect.SetWidth( 792.0 );
            rect.SetHeight( 1224.0 );
            break;

        default:
            break;
    }

    if( bLandscape ) 
    {
        double dTmp = rect.GetWidth();
        rect.SetWidth ( rect.GetHeight() );
        rect.SetHeight(  dTmp );
    }

    return rect;
}

const PdfObject* PdfPage::GetInheritedKeyFromObject( const char* inKey, const PdfObject* inObject ) const
{
    const PdfObject* pObj = NULL;

    // check for it in the object itself
    if ( inObject->GetDictionary().HasKey( inKey ) ) 
    {
        pObj = inObject->GetDictionary().GetKey( inKey );
        if ( !pObj->IsNull() ) 
            return pObj;
    }
    
    // if we get here, we need to go check the parent - if there is one!
    if( inObject->GetDictionary().HasKey( "Parent" ) ) 
    {
        pObj = inObject->GetIndirectKey( "Parent" );
        if( pObj )
            pObj = GetInheritedKeyFromObject( inKey, pObj );
    }

    return pObj;
}

const PdfRect PdfPage::GetPageBox( const char* inBox ) const
{
    PdfRect	 pageBox;
    const PdfObject*   pObj;
        
    // Take advantage of inherited values - walking up the tree if necessary
    pObj = GetInheritedKeyFromObject( inBox, this->GetObject() );
    

    // Sometime page boxes are defined using reference objects
    while ( pObj && pObj->IsReference() )
    {
        pObj = this->GetObject()->GetOwner()->GetObject( pObj->GetReference() );
    }

    // assign the value of the box from the array
    if ( pObj && pObj->IsArray() )
    {
        pageBox.FromArray( pObj->GetArray() );
    }
    else if ( strcmp( inBox, "ArtBox" ) == 0   ||
              strcmp( inBox, "BleedBox" ) == 0 ||
              strcmp( inBox, "TrimBox" ) == 0  )
    {
        // If those page boxes are not specified then
        // default to CropBox per PDF Spec (3.6.2)
        pageBox = GetPageBox( "CropBox" );
    }
    else if ( strcmp( inBox, "CropBox" ) == 0 )
    {
        // If crop box is not specified then
        // default to MediaBox per PDF Spec (3.6.2)
        pageBox = GetPageBox( "MediaBox" );
    }
    
    return pageBox;
}

int PdfPage::GetRotation() const 
{ 
    int rot = 0;
    
    const PdfObject* pObj = GetInheritedKeyFromObject( "Rotate", this->GetObject() ); 
    if ( pObj && pObj->IsNumber() )
        rot = static_cast<int>(pObj->GetNumber());
    
    return rot;
}

void PdfPage::SetRotation(int nRotation)
{
    if( nRotation != 0 && nRotation != 90 && nRotation != 180 && nRotation != 270 )
        PODOFO_RAISE_ERROR( ePdfError_ValueOutOfRange );

    this->GetObject()->GetDictionary().AddKey( "Rotate", PdfVariant(static_cast<pdf_int64>(nRotation)) );
}

PdfObject* PdfPage::GetAnnotationsArray( bool bCreate ) const
{
    PdfObject* pObj;

    // check for it in the object itself
    if ( this->GetObject()->GetDictionary().HasKey( "Annots" ) ) 
    {
        pObj = this->GetObject()->GetIndirectKey( "Annots" );
        if( pObj && pObj->IsArray() )
            return pObj;
    }
    else if( bCreate ) 
    {
        PdfArray array;
        this->GetNonConstObject()->GetDictionary().AddKey( "Annots", array );
        return const_cast<PdfObject*>(this->GetObject()->GetDictionary().GetKey( "Annots" ));
    }

    return NULL;
}

// added by Petr P. Petrov 21 Febrary 2010
bool PdfPage::SetPageWidth(int newWidth)
{
    PdfObject*   pObjMediaBox;
        
    // Take advantage of inherited values - walking up the tree if necessary
    pObjMediaBox = const_cast<PdfObject*>(GetInheritedKeyFromObject( "MediaBox", this->GetObject() ));
    
    // assign the value of the box from the array
    if ( pObjMediaBox && pObjMediaBox->IsArray() )
    {
        pObjMediaBox->GetArray()[2].SetNumber(newWidth);

        PdfObject*   pObjCropBox;

        // Take advantage of inherited values - walking up the tree if necessary
        pObjCropBox = const_cast<PdfObject*>(GetInheritedKeyFromObject( "CropBox", this->GetObject() ));

        if ( pObjCropBox && pObjCropBox->IsArray() )
        {
            pObjCropBox->GetArray()[2].SetNumber(newWidth);
            return true;
        }else
        {
            return false;
        }
    }else
    {
        return false;
    }
}

// added by Petr P. Petrov 21 Febrary 2010
bool PdfPage::SetPageHeight(int newHeight)
{
    PdfObject*   pObj;
        
    // Take advantage of inherited values - walking up the tree if necessary
    pObj = const_cast<PdfObject*>(GetInheritedKeyFromObject( "MediaBox", this->GetObject() ));
    
    // assign the value of the box from the array
    if ( pObj && pObj->IsArray() )
    {
        pObj->GetArray()[3].SetNumber(newHeight);

        PdfObject*   pObjCropBox;

        // Take advantage of inherited values - walking up the tree if necessary
        pObjCropBox = const_cast<PdfObject*>(GetInheritedKeyFromObject( "CropBox", this->GetObject() ));

        if ( pObjCropBox && pObjCropBox->IsArray() )
        {
            pObjCropBox->GetArray()[3].SetNumber(newHeight);
            return true;
        }else
        {
            return false;
        }
    }else
    {
        return false;
    }
}

void PdfPage::SetTrimBox( const PdfRect & rSize )
{
    PdfVariant trimbox;
    rSize.ToVariant( trimbox );
    this->GetObject()->GetDictionary().AddKey( "TrimBox", trimbox );
}

unsigned int PdfPage::GetPageNumber() const
{
    unsigned int        nPageNumber = 0;
    PdfObject*          pParent     = this->GetObject()->GetIndirectKey( "Parent" );
    PdfReference ref                = this->GetObject()->Reference();

    while( pParent ) 
    {
        PdfObject* pKids = pParent->GetIndirectKey( "Kids" );
        if ( pKids != NULL )
        {
            const PdfArray& kids        = pKids->GetArray();
            PdfArray::const_iterator it = kids.begin();

            while( it != kids.end() && (*it).GetReference() != ref )
            {
                PdfObject* pNode = this->GetObject()->GetOwner()->GetObject( (*it).GetReference() );

                if( pNode->GetDictionary().GetKey( PdfName::KeyType ) != NULL 
                    && pNode->GetDictionary().GetKey( PdfName::KeyType )->GetName() == PdfName( "Pages" ) )
                {
                    PdfObject* pCount = pNode->GetIndirectKey( "Count" );
                    if( pCount != NULL ) {
                        nPageNumber += static_cast<int>(pCount->GetNumber());
                    }
                } else {
                    // if we do not have a page tree node, 
                    // we most likely have a page object:
                    // so the page count is 1
                    ++nPageNumber;
                }
                ++it;
            }
        }

        ref     = pParent->Reference();
        pParent = pParent->GetIndirectKey( "Parent" );
    }

    return ++nPageNumber;
}

PdfObject* PdfPage::GetFromResources( const PdfName & rType, const PdfName & rKey )
{
    if( m_pResources->GetDictionary().HasKey( rType ) ) 
    {
        // OC 15.08.2010 BugFix: Ghostscript creates here sometimes an indirect reference to a directory
     // PdfObject* pType = m_pResources->GetDictionary().GetKey( rType );
        PdfObject* pType = m_pResources->GetIndirectKey( rType );
        if( pType->IsDictionary() && pType->GetDictionary().HasKey( rKey ) )
        {
            const PdfReference & ref = pType->GetDictionary().GetKey( rKey )->GetReference();
            return this->GetObject()->GetOwner()->GetObject( ref );
        }
    }
    
    return NULL;
}


PdfObject* PdfPage::GetOwnAnnotationsArray( bool bCreate, PdfDocument *pDocument)
{
   PdfObject* pObj;

   if ( this->GetObject()->GetDictionary().HasKey( "Annots" ) )  {
      pObj = this->GetObject()->GetIndirectKey( "Annots" );
        
      if(!pObj) {
         pObj = this->GetObject()->GetDictionary().GetKey("Annots");
         if( pObj->IsReference() ) {
            if( !pDocument ) {
               PODOFO_RAISE_ERROR_INFO( ePdfError_InvalidHandle, "Object is a reference but does not have an owner!" );
            }

            pObj = pDocument->GetObjects()->GetObject( pObj->GetReference() );
            if(pObj) {
               pObj->SetOwner(this->GetObject()->GetOwner());
            }
         } else
            pObj->SetOwner( this->GetObject()->GetOwner() );// even directs might want an owner...
      }

      if( pObj && pObj->IsArray() )
         return pObj;
    }
    else if( bCreate ) 
    {
        PdfArray array;
        this->GetNonConstObject()->GetDictionary().AddKey( "Annots", array );
        return const_cast<PdfObject*>(this->GetObject()->GetDictionary().GetKey( "Annots" ));
    }

    return NULL;
}


};
