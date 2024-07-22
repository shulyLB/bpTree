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
    explicit IException(const IError& _error):error(_error) {
        msg = std::string("code:").append(std::to_string(this->error.code))
                .append(";msg:").append(this->error.desc);
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

const IError ERROR_PARAM_ERROR = IError(1000, std::string("ERROR_PARAM_ERROR"));
const IError ERROR_PARAM_ERROR_SPLIT = IError(1001, std::string("ERROR_PARAM_ERROR for splitLen"));

const IError ERROR_WHEN_INSERT = IError(2000, std::string("ERROR_WHEN_INSERT"));
const IError ERROR_WHEN_INSERT_INDEX_NO_HAVE_SON = IError(2001, std::string("索引节点没有儿子"));


const IError ERROR_WHEN_DELETE = IError(3000, std::string("ERROR_WHEN_DELETE"));
const IError ERROR_WHEN_DELETE_WHERE_THE_NODE = IError(3001, std::string("非根没有左右节点！"));


const IError ERROR_WHEN_QUERY = IError(4000, std::string("ERROR_WHEN_QUERY"));

#endif //BPTREE_IEXCEPTION_H
