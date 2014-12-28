#include "MockImageProvider.h"

#include <KronApplication/ComicViewerViewModel.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

using ::testing::_;

class TestComicViewerViewModel : public testing::Test
{
protected:
    std::unique_ptr<MockImageProvider> _comic_provider;
    std::unique_ptr<ComicViewerViewModel> _comic_viewer;

    virtual void SetUp()
    {
        _comic_provider.reset(new MockImageProvider);
        _comic_viewer.reset(new ComicViewerViewModel(*_comic_provider));
    }

    virtual void TearDown()
    {
        _comic_viewer.release();
        _comic_provider.release();
    }
};

TEST_F(TestComicViewerViewModel, test_loadFile_setFirstImageOfComic_whenFileExist)
{
    // Arrange
    EXPECT_CALL(*_comic_provider, setPixmap(_));

    // Act
    _comic_viewer->nextPage();

    // Assert
    EXPECT_TRUE(true);
}
