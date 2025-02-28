#ifndef QPDF_DICTIONARY_HH
#define QPDF_DICTIONARY_HH

#include <qpdf/QPDFObject.hh>

#include <set>
#include <map>

#include <qpdf/QPDFObjectHandle.hh>

class QPDF_Dictionary: public QPDFObject
{
  public:
    QPDF_Dictionary(std::map<std::string, QPDFObjectHandle> const& items);
    virtual ~QPDF_Dictionary();
    virtual std::string unparse();
    virtual JSON getJSON();
    virtual QPDFObject::object_type_e getTypeCode() const;
    virtual char const* getTypeName() const;
    virtual void setDescription(QPDF*, std::string const&);

    // hasKey() and getKeys() treat keys with null values as if they
    // aren't there.  getKey() returns null for the value of a
    // non-existent key.  This is as per the PDF spec.
    bool hasKey(std::string const&);
    QPDFObjectHandle getKey(std::string const&);
    std::set<std::string> getKeys();
    std::map<std::string, QPDFObjectHandle> const& getAsMap() const;

    // Replace value of key, adding it if it does not exist
    void replaceKey(std::string const& key, QPDFObjectHandle);
    // Remove key, doing nothing if key does not exist
    void removeKey(std::string const& key);
    // If object is null, remove key; otherwise, replace key
    void replaceOrRemoveKey(std::string const& key, QPDFObjectHandle);

  protected:
    virtual void releaseResolved();

  private:
    std::map<std::string, QPDFObjectHandle> items;
};

#endif // QPDF_DICTIONARY_HH
