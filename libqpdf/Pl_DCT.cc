#include <qpdf/Pl_DCT.hh>

#include <qpdf/QIntC.hh>
#include <qpdf/QTC.hh>

#include <csetjmp>
#include <stdexcept>
#include <string>

//#if BITS_IN_JSAMPLE != 8
//# error "qpdf does not support libjpeg built with BITS_IN_JSAMPLE != 8"
//#endif

Pl_DCT::Members::Members(
    action_e action,
    char const* buf_description,
    JDIMENSION image_width,
    JDIMENSION image_height,
    int components,
    J_COLOR_SPACE color_space,
    CompressConfig* config_callback) :
    action(action),
    buf(buf_description),
    image_width(image_width),
    image_height(image_height),
    components(components),
    color_space(color_space),
    config_callback(config_callback)
{
}

Pl_DCT::Pl_DCT(char const* identifier, Pipeline* next) :
    Pipeline(identifier, next),
    m(new Members(a_decompress, "DCT compressed image"))
{
}

Pl_DCT::Pl_DCT(
    char const* identifier,
    Pipeline* next,
    JDIMENSION image_width,
    JDIMENSION image_height,
    int components,
    J_COLOR_SPACE color_space,
    CompressConfig* config_callback) :
    Pipeline(identifier, next),
    m(new Members(
        a_compress,
        "DCT uncompressed image",
        image_width,
        image_height,
        components,
        color_space,
        config_callback))
{
}

Pl_DCT::~Pl_DCT() // NOLINT (modernize-use-equals-default)
{
    // Must be explicit and not inline -- see QPDF_DLL_CLASS in README-maintainer
}

void
Pl_DCT::write(unsigned char const* data, size_t len)
{
    m->buf.write(data, len);
}

void
Pl_DCT::finish()
{
    m->buf.finish();
}

void
Pl_DCT::compress(void* cinfo_p, Buffer* b)
{
    throw "not implemented";
}

void
Pl_DCT::decompress(void* cinfo_p, Buffer* b)
{
    throw "not implemented";
}
