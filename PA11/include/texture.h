#ifndef TEXTURE_H
#define	TEXTURE_H
#define MAGICKCORE_HDRI_ENABLE 0
#define MAGICKCORE_QUANTUM_DEPTH 16

#include <string>

#include <GL/glew.h>
#include <ImageMagick-6/Magick++.h>
#include "graphics_headers.h"

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    Magick::Image m_image;
    Magick::Blob m_blob;
};


#endif	/* TEXTURE_H */
