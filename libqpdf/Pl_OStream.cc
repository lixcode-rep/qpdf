#include <qpdf/Pl_OStream.hh>

#include <stdexcept>

Pl_OStream::Members::Members(std::ostream& os) :
    os(os)
{
}

Pl_OStream::Pl_OStream(char const* identifier, std::ostream& os) :
    Pipeline(identifier, nullptr),
    m(new Members(os))
{
}

Pl_OStream::~Pl_OStream() // NOLINT (modernize-use-equals-default)
{
    // Must be explicit and not inline -- see QPDF_DLL_CLASS in README-maintainer
}

void
Pl_OStream::write(unsigned char const* buf, size_t len)
{
    m->os.write(reinterpret_cast<char const*>(buf), static_cast<std::streamsize>(len));
}

void
Pl_OStream::finish()
{
    m->os.flush();
}
