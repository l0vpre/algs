#include <string>

struct Hash
{
  public:
    size_t operator()(const std::string &s)
    {
        size_t hash = 0;
        for (size_t i = 0; i < s.length(); i++)
        {
            hash += s[i] * 2861;
            hash = (hash << 16) ^ hash;
            hash = (hash ^ (hash >> 24));
        }

        return hash;
    }
};

struct Djb2Hash
{
  public:
    size_t operator()(const std::string &s)
    {
        size_t hash = 5381;
        for (char c : s)
        {
            hash = ((hash << 5) + hash) + c;
        }

        return hash;
    }
};
