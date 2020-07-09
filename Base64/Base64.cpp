#include "Base64.h"

const char Base64::mapping[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Base64::operator char() const
{
    char num = 0;
    num |= (bit5 ? 1 : 0);
    num <<= 1;
    num |= (bit4 ? 1 : 0);
    num <<= 1;
    num |= (bit3 ? 1 : 0);
    num <<= 1;
    num |= (bit2 ? 1 : 0);
    num <<= 1;
    num |= (bit1 ? 1 : 0);
    num <<= 1;
    num |= (bit0 ? 1 : 0);
    return mapping[num];
}

char* Base64::encode(const char* inp_str, const int& inp_len)
{
    int out_len = (inp_len * 8) / 6;
    switch (inp_len % 3)
    {
    case 1:
        out_len += 2;
        break;
    case 2:
        out_len += 3;
        break;
    default:
        break;
    }
    
    char* out_str = new char[out_len  + 1]; // plus one for '\0' char at the end
    char* out_ptr = out_str;
    
    Base64 tmp_b64;
    short bit_counter = 0;
    bool tmp_bit;           // why bool?! cause it makes more sense than char
    char tmp_byte;          // why char?! cause its just 1 byte

    for (int i = 0; i < inp_len; i++)
    {
        tmp_byte = inp_str[i];
        for (int j = 0; j < 8; j++)
        {
            tmp_bit = tmp_byte & 128;
            tmp_byte <<= 1;

            switch (bit_counter)
            {
            case 0:
                tmp_b64.bit5 = tmp_bit;
                break;
            case 1:
                tmp_b64.bit4 = tmp_bit;
                break;
            case 2:
                tmp_b64.bit3 = tmp_bit;
                break;
            case 3:
                tmp_b64.bit2 = tmp_bit;
                break;
            case 4:
                tmp_b64.bit1 = tmp_bit;
                break;
            case 5:
                tmp_b64.bit0 = tmp_bit;
                break;
            default:
                break;
            }

            bit_counter++;
            if (bit_counter == 6)
            {
                *out_ptr = tmp_b64;
                out_ptr++;
                bit_counter = 0;
            }
        }
    }

    int num_of_paddings = 0;
    if (bit_counter == 2)
    {
        tmp_b64.bit3 = 0;
        tmp_b64.bit2 = 0;
        tmp_b64.bit1 = 0;
        tmp_b64.bit0 = 0;
        *out_ptr = tmp_b64;
        out_ptr++;
        bit_counter = 0;
        num_of_paddings = 2;
    }
    if (bit_counter == 4)
    {
        tmp_b64.bit1 = 0;
        tmp_b64.bit0 = 0;
        *out_ptr = tmp_b64;
        out_ptr++;
        bit_counter = 0;
        num_of_paddings = 1;
    }

    if (num_of_paddings > 1)
        *(out_ptr++) = '=';
    if (num_of_paddings > 0)
        *(out_ptr++) = '=';
    
    *out_ptr = '\0';

    return out_str;
}

char* Base64::decode(const char* inp_str, const int& inp_len)
{
    int out_len = (inp_len * 6) / 8;

    if (inp_str[inp_len - 1] == '=')
        out_len--;
    if (inp_str[inp_len - 2] == '=')
        out_len--;

    char* out_str = new char[out_len + 1]; // plus one for '\0' char at the end
    char* out_ptr = out_str;

    short bit_counter = 0;
    char tmp_ch;
    char tmp_6bit;

    for (int i = 0; i < inp_len; i++)
    {
        tmp_ch = inp_str[i];
        if (tmp_ch == '=')
            break;
        else if (tmp_ch >= 'A' && tmp_ch <= 'Z')
            tmp_6bit = tmp_ch - 'A';
        else if (tmp_ch >= 'a' && tmp_ch <= 'z')
            tmp_6bit = tmp_ch - 'a' + 26;
        else if (tmp_ch >= '0' && tmp_ch <= '9')
            tmp_6bit = tmp_ch - '0' + 52;
        else if (tmp_ch == '+')
            tmp_6bit = 62;
        else if (tmp_ch == '/')
            tmp_6bit = 63;
        else
            tmp_6bit = 0;
        tmp_6bit <<= 2;

        for (int j = 0; j < 6; j++)
        {
            if ((tmp_6bit & 0b10000000))  // explicit operator ordering is required
                *out_ptr |= 0b00000001;
            else
                *out_ptr &= 0b11111110;
            
            tmp_6bit <<= 1;

            bit_counter++;
            if (bit_counter == 8)
            {
                bit_counter = 0;
                out_ptr++;
            }
            else
                *out_ptr <<= 1;
        }
    }

    *out_ptr = '\0';

    return out_str;
}
