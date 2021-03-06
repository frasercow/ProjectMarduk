#ifndef FILESTREAM_H
#define FILESTREAM_H
#include "stream.h"
#include "common.h"

#include <memory>
#include <stdexcept>
#include <string>

struct FileStreamError : public StreamError {
    using StreamError::StreamError;
};

class FileStream : public virtual Stream
{
public:
    enum Mode
    {
        Read,
        Write,
        ReadWrite
    };

    explicit FileStream(std::string filePath, Mode mode = ReadWrite);
    virtual ~FileStream();

    virtual void seek(std::size_t position) const override;
    virtual std::size_t size() const override;
    virtual std::size_t tell() const override;
    virtual bool canRead() const override;
    virtual bool canWrite() const override;
    virtual void close();

protected:
    virtual std::size_t readsome(byte_t* data, std::size_t length) const override;
    virtual std::size_t writesome(const byte_t* data, std::size_t length) override;

private:
    struct FileStreamImpl;
    std::shared_ptr<FileStreamImpl> m_fs;
};

class InputFileStream final : public InputStream, public FileStream
{
public:
    InputFileStream(std::string filePath) : FileStream(std::move(filePath), Read) {}
private:
    using FileStream::write;
};

class OutputFileStream final : public FileStream
{
public:
    OutputFileStream(std::string filePath) : FileStream(std::move(filePath), Write) {}
private:
    using FileStream::read;
};

#endif // FILESTREAM_H
