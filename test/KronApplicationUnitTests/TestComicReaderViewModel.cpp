#include <KronApplication/services/ComicArchiveReader.h>
#include <KronApplication/services/ImageContainer.h>
#include <KronApplication/viewmodels/ComicReaderVM.h>

#include <gtest/gtest.h>
#include <HippoMocks/hippomocks.h>

#include <memory>

std::ostream& operator<<(std::ostream& stream, const QByteArray& byteArray)
{
    stream << byteArray.toStdString();
    return stream;
}

namespace kron {

class TestComicViewerViewModel : public ::testing::Test
{
protected:
    std::unique_ptr<MockRepository> mocks_;
    ComicArchiveReader* comicArchiveReader_;
    ImageContainer* imageContainer_;
    std::unique_ptr<ComicReaderVM> comicReader_;

    virtual void SetUp()
    {
        mocks_.reset(new MockRepository);
        comicArchiveReader_ = mocks_->Mock<ComicArchiveReader>();
        imageContainer_ = mocks_->Mock<ImageContainer>();
        comicReader_.reset(new ComicReaderVM(*comicArchiveReader_, *imageContainer_));
    }

    virtual void TearDown()
    {
        comicReader_.release();
        mocks_.release();
    }
};

TEST_F(TestComicViewerViewModel, shouldGoToFirstPageWhenComicLoaded)
{
    QString testComic = "TestComic.cbz";
    QByteArray expectedPage = "ExpectedPage";
    QString id = "current";
    mocks_->ExpectCall(comicArchiveReader_, ComicArchiveReader::open).With(testComic);
    mocks_->ExpectCall(comicArchiveReader_, ComicArchiveReader::readFirstImage).Return(expectedPage);
    mocks_->ExpectCall(imageContainer_, ImageContainer::setImage).With(id, expectedPage);

    comicReader_->openComic(testComic);

    EXPECT_NO_THROW(mocks_->VerifyAll());
}

}
