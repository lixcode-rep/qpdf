// Copyright (c) 2005-2024 Jay Berkenbilt
//
// This file is part of qpdf.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under
// the License.
//
// Versions of qpdf prior to version 7 were released under the terms of version 2.0 of the Artistic
// License. At your option, you may continue to consider qpdf to be licensed under those terms.
// Please see the manual for additional information.

#ifndef PL_DCT_HH
#define PL_DCT_HH

#include <qpdf/Pipeline.hh>

#include <qpdf/Pl_Buffer.hh>
#include <cstddef>

// jpeglib.h must be included after cstddef or else it messes up the definition of size_t.
//#include <jpeglib.h>
typedef unsigned int JDIMENSION;
typedef enum {
    JCS_UNKNOWN,            /* error/unspecified */
    JCS_GRAYSCALE,          /* monochrome */
    JCS_RGB,                /* red/green/blue as specified by the RGB_RED,
                             RGB_GREEN, RGB_BLUE, and RGB_PIXELSIZE macros */
    JCS_YCbCr,              /* Y/Cb/Cr (also known as YUV) */
    JCS_CMYK,               /* C/M/Y/K */
    JCS_YCCK,               /* Y/Cb/Cr/K */
    JCS_EXT_RGB,            /* red/green/blue */
    JCS_EXT_RGBX,           /* red/green/blue/x */
    JCS_EXT_BGR,            /* blue/green/red */
    JCS_EXT_BGRX,           /* blue/green/red/x */
    JCS_EXT_XBGR,           /* x/blue/green/red */
    JCS_EXT_XRGB,           /* x/red/green/blue */
    /* When out_color_space it set to JCS_EXT_RGBX, JCS_EXT_BGRX, JCS_EXT_XBGR,
     or JCS_EXT_XRGB during decompression, the X byte is undefined, and in
     order to ensure the best performance, libjpeg-turbo can set that byte to
     whatever value it wishes.  Use the following colorspace constants to
     ensure that the X byte is set to 0xFF, so that it can be interpreted as an
     opaque alpha channel. */
    JCS_EXT_RGBA,           /* red/green/blue/alpha */
    JCS_EXT_BGRA,           /* blue/green/red/alpha */
    JCS_EXT_ABGR,           /* alpha/blue/green/red */
    JCS_EXT_ARGB,           /* alpha/red/green/blue */
    JCS_RGB565              /* 5-bit red/6-bit green/5-bit blue */
} J_COLOR_SPACE;

class QPDF_DLL_CLASS Pl_DCT: public Pipeline
{
  public:
    // Constructor for decompressing image data
    QPDF_DLL
    Pl_DCT(char const* identifier, Pipeline* next);

    class QPDF_DLL_CLASS CompressConfig
    {
      public:
        QPDF_DLL
        CompressConfig() = default;
        QPDF_DLL
        virtual ~CompressConfig() = default;
        virtual void apply(void*) = 0;
    };

    // Constructor for compressing image data
    QPDF_DLL
    Pl_DCT(
        char const* identifier,
        Pipeline* next,
        JDIMENSION image_width,
        JDIMENSION image_height,
        int components,
        J_COLOR_SPACE color_space,
        CompressConfig* config_callback = nullptr);

    QPDF_DLL
    ~Pl_DCT() override;

    QPDF_DLL
    void write(unsigned char const* data, size_t len) override;
    QPDF_DLL
    void finish() override;

  private:
    QPDF_DLL_PRIVATE
    void compress(void* cinfo, Buffer*);
    QPDF_DLL_PRIVATE
    void decompress(void* cinfo, Buffer*);

    enum action_e { a_compress, a_decompress };

    class QPDF_DLL_PRIVATE Members
    {
        friend class Pl_DCT;

      public:
        QPDF_DLL
        ~Members() = default;

      private:
        Members(
            action_e action,
            char const* buf_description,
            JDIMENSION image_width = 0,
            JDIMENSION image_height = 0,
            int components = 1,
            J_COLOR_SPACE color_space = JCS_GRAYSCALE,
            CompressConfig* config_callback = nullptr);
        Members(Members const&) = delete;

        action_e action;
        Pl_Buffer buf;

        // Used for compression
        JDIMENSION image_width;
        JDIMENSION image_height;
        int components;
        J_COLOR_SPACE color_space;

        CompressConfig* config_callback;
    };

    std::shared_ptr<Members> m;
};

#endif // PL_DCT_HH
