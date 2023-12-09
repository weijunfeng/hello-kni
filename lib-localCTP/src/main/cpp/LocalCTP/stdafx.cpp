#include "stdafx.h"
#include "iconv.h"
#include "iostream"

namespace localCTP
{

    class converter
    {
    public:
        converter(const std::string& out_encode,
                  const std::string& in_encode,
                  bool               ignore_error = false,
                  size_t             buf_size     = 1024)
                : m_ignore_error(ignore_error), m_buf_size(buf_size)
        {
            if (buf_size == 0)
            {
                throw std::runtime_error("buffer size must be greater than zero");
            }

            iconv_t conv = ::iconv_open(out_encode.c_str(), in_encode.c_str());
            if (conv == (iconv_t)-1)
            {
                if (errno == EINVAL)
                {
                    throw std::runtime_error("not supported from " + in_encode + " to " + out_encode);
                }
                else
                {
                    throw std::runtime_error("unknown error");
                }
            }
            m_iconv = conv;
        }

        ~converter()
        {
            iconv_close(m_iconv);
        }

        void convert(const std::string& input, std::string& output) const
        {
            std::vector<char> in_buf(input.begin(), input.end());
            char*             src_ptr  = &in_buf[0];
            size_t            src_size = input.size();

            std::vector<char> buf(m_buf_size);
            std::string       dst;
            while (0 < src_size)
            {
                char*  dst_ptr  = &buf[0];
                size_t dst_size = buf.size();
                size_t res      = ::iconv(m_iconv, &src_ptr, &src_size, &dst_ptr, &dst_size);
                if (res == (size_t)-1)
                {
                    if (errno == E2BIG)
                    {}
                    else if (m_ignore_error)
                    {
                        ++src_ptr;
                        --src_size;
                    }
                    else
                    {
                        check_convert_error();
                    }
                }
                dst.append(&buf[0], buf.size() - dst_size);
            }
            dst.swap(output);
        }

    private:
        static void check_convert_error()
        {
            switch (errno)
            {
                case EILSEQ:
                case EINVAL:
                    throw std::runtime_error("invalid multibyte chars");
                default:
                    throw std::runtime_error("unknown error");
            }
        }

        iconv_t      m_iconv;
        bool         m_ignore_error;
        const size_t m_buf_size;
    };

std::string gbk_to_utf8(const std::string& str)
{
    converter   conv("UTF-8", "GBK", true, 1024);
    std::string output;
    try
    {
        conv.convert(str, output);
    }
    catch (const std::exception& e)
    {
        std::cerr << "gbk_to_utf8 exception:" << e.what() << std::endl;
    }
    return output;
}

std::string utf8_to_gbk(const std::string& str)
{
    converter   conv("GBK", "UTF-8", true, 1024);
    std::string output;
    try
    {
        conv.convert(str, output);
    }
    catch (const std::exception& e)
    {
        std::cerr << "utf8_to_gbk exception:" << e.what() << std::endl;
    }
    return output;
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}

std::string base64_decode(std::string const& encoded_string)
{
    size_t in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}

} // end namespace localCTP
