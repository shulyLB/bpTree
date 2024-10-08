//
// Created by libao02 on 2024/7/22.
//

#ifndef BPTREE_IEXCEPTION_H
#define BPTREE_IEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class IError {
private:
    int code;
    std::string desc;
public:
    friend IException;
    IError(int _code, std::string _desc) {
        this->code = _code;
        this->desc = std::move(_desc);
    }
};

class IException : public std::exception {
private:
    IError error;
    std::string msg;
public:
    explicit IException(IError _error):error(std::move(_error)) {
        msg = std::string("code:").append(std::to_string(this->error.code))
                .append(";msg:").append(this->error.desc);
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// 初始化报错
const IError ERROR_INIT_ILLEGAL_NODE_NUMBER_ERROR = IError(-1, std::string("最小结点数量过低"));

// 插入报错
const IError ERROR_WHEN_INSERT = IError(2000, std::string("ERROR_WHEN_INSERT"));
const IError ERROR_WHEN_INSERT_INDEX_NO_HAVE_SON = IError(2001, std::string("索引节点没有儿子"));
const IError ERROR_WHEN_INSERT_PARAM_ERROR_SPLIT = IError(1001, std::string("ERROR_PARAM_ERROR for splitLen"));

// 删除报错
const IError ERROR_WHEN_DELETE = IError(3000, std::string("ERROR_WHEN_DELETE"));
const IError ERROR_WHEN_DELETE_WHERE_THE_NODE = IError(3001, std::string("非根没有左右节点！"));

// 查询报错
const IError ERROR_WHEN_QUERY = IError(4000, std::string("ERROR_WHEN_QUERY"));

#endif //BPTREE_IEXCEPTION_H
