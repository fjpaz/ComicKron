#ifndef MOCKIMAGEPROVIDER_H
#define MOCKIMAGEPROVIDER_H

#include <gmock/gmock.h>

#include <KronApplication/ComicImageProvider.h>

class MockImageProvider : public ComicImageProvider
{
public:
    MOCK_CONST_METHOD0(flags, Flags());
    MOCK_CONST_METHOD0(imageType, ImageType());
    MOCK_METHOD3(requestImage, QImage(const QString & id, QSize * size, const QSize & requestedSize));
    MOCK_METHOD3(requestPixmap, QPixmap(const QString &id, QSize *size, const QSize &requestedSize));
    MOCK_METHOD3(requestTexture, QQuickTextureFactory*(const QString & id, QSize * size, const QSize & requestedSize));
    MOCK_METHOD1(setPixmap, void(const QPixmap &pixmap));
};

#endif // MOCKIMAGEPROVIDER_H
