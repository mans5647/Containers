#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>



class String
{
    private:
    mutable char * arr;
    size_t length = 0;
    public:
    String(const char * str);
    String()
    {
        arr = nullptr;
    }
    ~String()
    {
        delete[]arr;
    }
    inline size_t size() const;
    inline bool is_empty() const;
    String& concat(const char * str);
    String& concat(const String& str);
    String& join(const char * str, const char & delim);
    inline char & symbol_at(const size_t index) const;

    inline bool equal(const String& rhs);
    inline bool equal(const char * str);
    
    String trim() // returns a new strin without spaces
    {
        String returning_string;
        for (size_t iter = 0; iter < length; iter++)
        {
            if (std::isalpha(arr[iter]) != 0)
            {
                returning_string += arr[iter];
            }
            if (std::isspace(arr[iter]) != 0)
            {
                arr[iter++];
            }
        }
        return returning_string;
    }
    
    
    protected:
    inline bool common_equal(const char * lhs, const String& rhs);
    inline bool common_equal(const char * str1, const char* str);



    public:
    String& operator=(const char * str);
    String& operator=(const char& ch);
    String& operator=(const String& str);
    String& operator+=(const char * str);
    String& operator+=(const char & ch);
    String& operator+=(const String& str);
    inline bool operator==(const String & rhs);
    inline bool operator==(const char* str);
    

    String operator+(const char * rhs)
    {
        size_t old_size = length;
        length = length + strlen(rhs);
        char * tmp = new char[length];
        for (size_t i = 0; i < old_size + 1; i++)
        {
            tmp[i] = arr[i];
        }
        size_t st = 0;
        for (size_t i = old_size; i < length + 1; i++)
        {
            tmp[i] = rhs[st++];
        }
        delete [] arr;
        arr = new char[length + 1];
        strcpy(arr, tmp);
        return arr;
    }

    
    String operator+(const String& rhs)
    {
        size_t old_length = length;
        length = length + rhs.size();
        char * tmp = new char[length + 1];
        for (size_t i = 0; i < old_length; i++)
        {
            tmp[i] = arr[i];
        }
        delete [] arr;
        size_t st = 0;
        for (size_t i = old_length; i < length + 1; i++)
        {
            tmp[i] = rhs[st++];
        }
        arr = new char[length + 1];
        strcpy(arr, tmp);
        delete [] tmp;
        return arr;
    }

    


    inline char &operator[](const size_t index) const noexcept
    {
        
        return arr[index];
    }
    friend std::ostream& operator<<(std::ostream & os,const  String&str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            os << str[i];
        }

        return os;
    }

};

String::String(const char * str)
{
    size_t len = strlen(str);
    arr = new char[len];
    strcpy(arr, str);
    length = len;
}

inline size_t String::size() const
{
    return length;
}

String& String::operator=(const char * str)
{
    delete[] arr;
    size_t len = strlen(str);
    length = len;
    arr = new char[length];
    for (size_t i = 0; i < length; i++)
    {
        arr[i] = str[i];
    }

    return *this;
}

String& String::operator=(const char &ch)
{
    delete[] arr;
    arr = new char[1];
    length = 1;
    arr[length - 1] = ch;

    return *this; 
}

String& String::operator=(const String& str)
{
    if (this == &str)
    {
        return *this;
    }
    delete[] arr;
    arr = new char[str.size()];
    length = str.size();
    for (size_t i = 0; i < length; i++)
    {
        this->arr[i] = str[i];
    }

    return *this;
}

String& String::operator+=(const char * str)
{
    size_t old = length;
    length = length + strlen(str);
    char * tmp = new char[old + 1];
    strcpy(tmp, arr);
    delete [] arr;
    arr = new char[length+1];
    strcpy(arr, tmp);
    delete [] tmp;
    size_t sr = 0;
    for (size_t i = old; i < length + 1; i++)
    {
        arr[i] = str[sr++];
    }
    return *this;
}

String& String::operator+=(const char & ch)
{
    char * tmp = new char[length + 1];
    for (uint32_t i = 0; i < length; i++)
    {
        tmp[i] = arr[i];
    }
    tmp[length] = ch;
    delete [] arr;
    length+=1;
    arr = new char[length];
    for (uint32_t i = 0; i < length; i++)
    {
        arr[i] = tmp[i];
    }

    return *this;
    
}

String& String::operator+=(const String& str)
{
    size_t old_length = length;
    char * tmp = new char[length];

    strcpy(tmp, arr);

    delete [] arr;
    length+=str.size();

    arr = new char[length];

    strcpy(arr, tmp);

    auto k = 0;

    for (auto i = old_length; i < length + 1; i++)
    {
        arr[i] = str[k++];
    }

    return *this;
}

inline bool String::is_empty() const
{
    return (length == 0) ? true : false;
}

String& String::concat(const char * str)
{
    String str_temp = str;
    size_t old_size = length;
    char * tmp = new char[length];

    strcpy(tmp, arr);

    delete[] arr;

    length+=str_temp.size();
    arr = new char[length];

    strcpy(arr, tmp);

    delete[] tmp;

    auto k = 0;
    for (size_t i = old_size; i < length + 1; i++)
    {
        arr[i] = str_temp[k++];
    }

    return *this;   

}

String& String::join(const char * str, const char & delim)
{

    auto old_sz = length;
    char * tmp = new char[length];
    for (auto i = 0; i < length; i++)
    {
        tmp[i] = arr[i];
    }

    delete[] arr;

    length = length + 1 + strlen(str);
    arr = new char[length];
    for (auto i = 0; i < old_sz; i++)
    {
        arr[i] = tmp[i];
    }

    arr[old_sz] = delim;
    auto st = 0;
    for (auto i = old_sz + 1; i < length; i++)
    {
        arr[i] = str[st++];
    }
    delete[] tmp;
    return *this;

    
}

inline char & String::symbol_at(const size_t index) const
{
    if ((index > length - 1) | (index < 0)) throw std::invalid_argument("Index out of bound");
    return arr[index];
}

inline bool String::equal(const String& rhs)
{
    return (common_equal(arr, rhs)) ? true : false;
}

inline bool String::equal(const char * str)
{
    return (common_equal(arr, str)) ? true : false;
}

inline bool String::common_equal(const char * lhs, const String& rhs)
{
    for (auto i = 0; i < size(); i++)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    
    return true;
}

inline bool String::common_equal(const char * str1, const char * str)
{
    for (auto i = 0; i < size(); i++)
    {
        if (str1[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

inline bool String::operator==(const String & rhs)
{
    return (common_equal(arr, rhs)) ? true : false;
}

inline bool String::operator==(const char * str)
{
    return (common_equal(arr, str)) ? true : false;
}


#endif // STRING_H