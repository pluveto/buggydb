# buggydb

buggydb is a buggy file based database system. Design by ZhangZijing.

Each table a binary file.

## Table

```
----------------------------
    typedef struct table_meta
    {
        char name[32];
        size_t size;
    } table_meta;

    record: {
        string key
        size_t value_size
        * value
        next
    }

----------------------------
```