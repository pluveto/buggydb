#include <stdio.h>
#include <cstring>
#include <buggydb/buggydb.hpp>

class user_model : public buggydb::value_interface
{
private:
    size_t _size;
    char _username[16];
    char _password[32];

public:
    user_model() = default;
    user_model(std::string username, std::string password)
    {
        strcpy(this->_username, username.c_str());
        strcpy(this->_password, password.c_str());
    }
    size_t size()
    {
        return sizeof(this->_username) + sizeof(this->_password);
    }
    std::string username()
    {
        return this->_username;
    }
    char *serialize()
    {
        char *buffer = new char[this->size()];
        auto o = this;
        memcpy(buffer, o->_username, sizeof(o->_username));
        memcpy(buffer + sizeof(o->_username), o->_password, sizeof(o->_password));
        return buffer;
    }
    static void *deserialize(char *buffer)
    {
        auto o = new user_model;
        memcpy(o->_username, buffer, sizeof(o->_username));
        memcpy(o->_password, buffer + sizeof(o->_username), sizeof(o->_password));
        return o;
    }
};

class article_model : public buggydb::value_interface
{
private:
    size_t _size;
    size_t _id;
    char _title[128];
    char *_content;
    size_t _content_size;

public:
    article_model() = default;
    article_model(size_t id, std::string title, std::string content)
    {
        this->_id = id;
        this->_size = sizeof(this->_id);

        strcpy(this->_title, title.c_str());
        this->_size += sizeof(this->_title);

        this->_content_size = content.size() + 1;
        this->_content = new char[_content_size];
        this->_size += _content_size;

        strcpy(this->_content, content.c_str());
    }
    size_t size()
    {
        return this->_size;
    }
    std::string title()
    {
        return this->_title;
    }
    size_t id()
    {
        return this->_id;
    }
    char *serialize()
    {
        char *buffer = new char[this->size()];
        auto o = this;
        size_t cursor = 0;

        memcpy(buffer + cursor, &o->_id, sizeof(o->_id));
        cursor += sizeof(o->_id);

        memcpy(buffer + cursor, o->_title, sizeof(o->_title));
        cursor += sizeof(o->_title);

        memcpy(buffer + cursor, &o->_content_size, sizeof(o->_content_size));
        cursor += sizeof(o->_content_size);

        memcpy(buffer + cursor, o->_content, o->_content_size);
        cursor += o->_content_size;

        return buffer;
    }
    static void *deserialize(char *buffer)
    {
        auto o = new article_model;
        size_t cursor = 0;

        memcpy(&o->_id, buffer + cursor, sizeof(o->_id));
        cursor += sizeof(o->_id);

        memcpy(o->_title, buffer + cursor, sizeof(o->_title));
        cursor += sizeof(o->_title);

        memcpy(&o->_content_size, buffer + cursor, sizeof(o->_content_size));
        cursor += sizeof(o->_content_size);

        memcpy(o->_content, buffer + cursor, o->_content_size);
        cursor += o->_content_size;
        return o;
    }
};

int main(int argc, char const *argv[])
{
    printf("hello, buggydb.\n");

    auto db = new buggydb::buggydb();
    db->base_dir("./db");

    auto user_table = db->create_table("user");

    auto xiaoming = new user_model("xiaoming", "112233abcabcabc");
    user_table->insert(xiaoming->username(), xiaoming);

    auto lihua = new user_model("lihua", "lhlhlhlh");
    user_table->insert(lihua->username(), lihua);

    auto pluveto = new user_model("pluveto", "pluvetopluvetopluvetopluveto");
    user_table->insert(pluveto->username(), pluveto);

    db->save_table(user_table);

    auto article_table = db->create_table("articles");
    auto article_1 = new article_model(article_table->record_length() + 1, "Hello, world",
                                       "expression preceding parentheses of apparent call must have (pointer-to-) function type\n"
                                       "argument of type \" char * \" is incompatible with parameter of type \"unsigned char *\"\n"
                                       "user-defined literal operator not found\n");
                                       
    article_table->insert(std::to_string(article_1->id()), article_1);

    auto article_2 = new article_model(article_table->record_length() + 1, "???????????????",
                                       "????????????NFA????????????????????????????????????DFA????????????\n"
                                       "\n"
                                       "?????????????????????NFA\n"
                                       "\n"
                                       "??(p, 0) = {q}\n"
                                       "??(p, 1) = ???\n"
                                       "??(q, 0) = {q}\n"
                                       "??(q, 1) = {q, r}\n"
                                       "??(r, 0) = ???\n"
                                       "??(r, 1) = ???\n"
                                       "??????DFA?????????????????????????????????{q, r}??????DFA????????????????????????q????????????r???????????????q????????????r????????????0????????????????????????????????????q????????????0??????????????????????????????r????????????0????????????????????????????????????????????????????????????\n"
                                       "\n"
                                       "??({q, r}, 0) = {q}\n"
                                       "??({q, r}, 1) = {q, r}\n");
    article_table->insert(std::to_string(article_2->id()), article_2);
    db->save_table(article_table);

    return 0;
}
