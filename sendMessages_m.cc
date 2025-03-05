//
// Generated file, do not edit! Created by opp_msgtool 6.0 from sendMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "sendMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(hostMessage)

hostMessage::hostMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

hostMessage::hostMessage(const hostMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

hostMessage::~hostMessage()
{
}

hostMessage& hostMessage::operator=(const hostMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void hostMessage::copy(const hostMessage& other)
{
    this->destinationAdd = other.destinationAdd;
    this->sourceAdd = other.sourceAdd;
    this->typeOfService = other.typeOfService;
    this->payloadLength = other.payloadLength;
    this->headerLength = other.headerLength;
    this->delay = other.delay;
}

void hostMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->destinationAdd);
    doParsimPacking(b,this->sourceAdd);
    doParsimPacking(b,this->typeOfService);
    doParsimPacking(b,this->payloadLength);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->delay);
}

void hostMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->destinationAdd);
    doParsimUnpacking(b,this->sourceAdd);
    doParsimUnpacking(b,this->typeOfService);
    doParsimUnpacking(b,this->payloadLength);
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->delay);
}

unsigned int hostMessage::getDestinationAdd() const
{
    return this->destinationAdd;
}

void hostMessage::setDestinationAdd(unsigned int destinationAdd)
{
    this->destinationAdd = destinationAdd;
}

unsigned int hostMessage::getSourceAdd() const
{
    return this->sourceAdd;
}

void hostMessage::setSourceAdd(unsigned int sourceAdd)
{
    this->sourceAdd = sourceAdd;
}

unsigned int hostMessage::getTypeOfService() const
{
    return this->typeOfService;
}

void hostMessage::setTypeOfService(unsigned int typeOfService)
{
    this->typeOfService = typeOfService;
}

unsigned int hostMessage::getPayloadLength() const
{
    return this->payloadLength;
}

void hostMessage::setPayloadLength(unsigned int payloadLength)
{
    this->payloadLength = payloadLength;
}

unsigned int hostMessage::getHeaderLength() const
{
    return this->headerLength;
}

void hostMessage::setHeaderLength(unsigned int headerLength)
{
    this->headerLength = headerLength;
}

double hostMessage::getDelay() const
{
    return this->delay;
}

void hostMessage::setDelay(double delay)
{
    this->delay = delay;
}

class hostMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destinationAdd,
        FIELD_sourceAdd,
        FIELD_typeOfService,
        FIELD_payloadLength,
        FIELD_headerLength,
        FIELD_delay,
    };
  public:
    hostMessageDescriptor();
    virtual ~hostMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(hostMessageDescriptor)

hostMessageDescriptor::hostMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(hostMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

hostMessageDescriptor::~hostMessageDescriptor()
{
    delete[] propertyNames;
}

bool hostMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<hostMessage *>(obj)!=nullptr;
}

const char **hostMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *hostMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int hostMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int hostMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destinationAdd
        FD_ISEDITABLE,    // FIELD_sourceAdd
        FD_ISEDITABLE,    // FIELD_typeOfService
        FD_ISEDITABLE,    // FIELD_payloadLength
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_delay
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *hostMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destinationAdd",
        "sourceAdd",
        "typeOfService",
        "payloadLength",
        "headerLength",
        "delay",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int hostMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destinationAdd") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceAdd") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "typeOfService") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "payloadLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "delay") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *hostMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_destinationAdd
        "unsigned int",    // FIELD_sourceAdd
        "unsigned int",    // FIELD_typeOfService
        "unsigned int",    // FIELD_payloadLength
        "unsigned int",    // FIELD_headerLength
        "double",    // FIELD_delay
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **hostMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *hostMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int hostMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void hostMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'hostMessage'", field);
    }
}

const char *hostMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string hostMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationAdd: return ulong2string(pp->getDestinationAdd());
        case FIELD_sourceAdd: return ulong2string(pp->getSourceAdd());
        case FIELD_typeOfService: return ulong2string(pp->getTypeOfService());
        case FIELD_payloadLength: return ulong2string(pp->getPayloadLength());
        case FIELD_headerLength: return ulong2string(pp->getHeaderLength());
        case FIELD_delay: return double2string(pp->getDelay());
        default: return "";
    }
}

void hostMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationAdd: pp->setDestinationAdd(string2ulong(value)); break;
        case FIELD_sourceAdd: pp->setSourceAdd(string2ulong(value)); break;
        case FIELD_typeOfService: pp->setTypeOfService(string2ulong(value)); break;
        case FIELD_payloadLength: pp->setPayloadLength(string2ulong(value)); break;
        case FIELD_headerLength: pp->setHeaderLength(string2ulong(value)); break;
        case FIELD_delay: pp->setDelay(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'hostMessage'", field);
    }
}

omnetpp::cValue hostMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationAdd: return (omnetpp::intval_t)(pp->getDestinationAdd());
        case FIELD_sourceAdd: return (omnetpp::intval_t)(pp->getSourceAdd());
        case FIELD_typeOfService: return (omnetpp::intval_t)(pp->getTypeOfService());
        case FIELD_payloadLength: return (omnetpp::intval_t)(pp->getPayloadLength());
        case FIELD_headerLength: return (omnetpp::intval_t)(pp->getHeaderLength());
        case FIELD_delay: return pp->getDelay();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'hostMessage' as cValue -- field index out of range?", field);
    }
}

void hostMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationAdd: pp->setDestinationAdd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_sourceAdd: pp->setSourceAdd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_typeOfService: pp->setTypeOfService(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_payloadLength: pp->setPayloadLength(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_headerLength: pp->setHeaderLength(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_delay: pp->setDelay(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'hostMessage'", field);
    }
}

const char *hostMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr hostMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void hostMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    hostMessage *pp = omnetpp::fromAnyPtr<hostMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'hostMessage'", field);
    }
}

Register_Class(obsMessage)

obsMessage::obsMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

obsMessage::obsMessage(const obsMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

obsMessage::~obsMessage()
{
    delete [] this->hostMessageGroup;
}

obsMessage& obsMessage::operator=(const obsMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void obsMessage::copy(const obsMessage& other)
{
    delete [] this->hostMessageGroup;
    this->hostMessageGroup = (other.hostMessageGroup_arraysize==0) ? nullptr : new hostMessage *[other.hostMessageGroup_arraysize];
    hostMessageGroup_arraysize = other.hostMessageGroup_arraysize;
    for (size_t i = 0; i < hostMessageGroup_arraysize; i++) {
        this->hostMessageGroup[i] = other.hostMessageGroup[i];
    }
    this->sourceAdd = other.sourceAdd;
    this->destinationAdd = other.destinationAdd;
    this->typeOfService = other.typeOfService;
    this->payloadLength = other.payloadLength;
    this->headerLength = other.headerLength;
    this->signalWavelenght = other.signalWavelenght;
    this->burstID = other.burstID;
}

void obsMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    b->pack(hostMessageGroup_arraysize);
    doParsimArrayPacking(b,this->hostMessageGroup,hostMessageGroup_arraysize);
    doParsimPacking(b,this->sourceAdd);
    doParsimPacking(b,this->destinationAdd);
    doParsimPacking(b,this->typeOfService);
    doParsimPacking(b,this->payloadLength);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->signalWavelenght);
    doParsimPacking(b,this->burstID);
}

void obsMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    delete [] this->hostMessageGroup;
    b->unpack(hostMessageGroup_arraysize);
    if (hostMessageGroup_arraysize == 0) {
        this->hostMessageGroup = nullptr;
    } else {
        this->hostMessageGroup = new hostMessage *[hostMessageGroup_arraysize];
        doParsimArrayUnpacking(b,this->hostMessageGroup,hostMessageGroup_arraysize);
    }
    doParsimUnpacking(b,this->sourceAdd);
    doParsimUnpacking(b,this->destinationAdd);
    doParsimUnpacking(b,this->typeOfService);
    doParsimUnpacking(b,this->payloadLength);
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->signalWavelenght);
    doParsimUnpacking(b,this->burstID);
}

size_t obsMessage::getHostMessageGroupArraySize() const
{
    return hostMessageGroup_arraysize;
}

const hostMessage * obsMessage::getHostMessageGroup(size_t k) const
{
    if (k >= hostMessageGroup_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hostMessageGroup_arraysize, (unsigned long)k);
    return this->hostMessageGroup[k];
}

void obsMessage::setHostMessageGroupArraySize(size_t newSize)
{
    hostMessage * *hostMessageGroup2 = (newSize==0) ? nullptr : new hostMessage *[newSize];
    size_t minSize = hostMessageGroup_arraysize < newSize ? hostMessageGroup_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        hostMessageGroup2[i] = this->hostMessageGroup[i];
    for (size_t i = minSize; i < newSize; i++)
        hostMessageGroup2[i] = nullptr;
    delete [] this->hostMessageGroup;
    this->hostMessageGroup = hostMessageGroup2;
    hostMessageGroup_arraysize = newSize;
}

void obsMessage::setHostMessageGroup(size_t k, hostMessage * hostMessageGroup)
{
    if (k >= hostMessageGroup_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hostMessageGroup_arraysize, (unsigned long)k);
    this->hostMessageGroup[k] = hostMessageGroup;
}

void obsMessage::insertHostMessageGroup(size_t k, hostMessage * hostMessageGroup)
{
    if (k > hostMessageGroup_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hostMessageGroup_arraysize, (unsigned long)k);
    size_t newSize = hostMessageGroup_arraysize + 1;
    hostMessage * *hostMessageGroup2 = new hostMessage *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hostMessageGroup2[i] = this->hostMessageGroup[i];
    hostMessageGroup2[k] = hostMessageGroup;
    for (i = k + 1; i < newSize; i++)
        hostMessageGroup2[i] = this->hostMessageGroup[i-1];
    delete [] this->hostMessageGroup;
    this->hostMessageGroup = hostMessageGroup2;
    hostMessageGroup_arraysize = newSize;
}

void obsMessage::appendHostMessageGroup(hostMessage * hostMessageGroup)
{
    insertHostMessageGroup(hostMessageGroup_arraysize, hostMessageGroup);
}

void obsMessage::eraseHostMessageGroup(size_t k)
{
    if (k >= hostMessageGroup_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hostMessageGroup_arraysize, (unsigned long)k);
    size_t newSize = hostMessageGroup_arraysize - 1;
    hostMessage * *hostMessageGroup2 = (newSize == 0) ? nullptr : new hostMessage *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hostMessageGroup2[i] = this->hostMessageGroup[i];
    for (i = k; i < newSize; i++)
        hostMessageGroup2[i] = this->hostMessageGroup[i+1];
    delete [] this->hostMessageGroup;
    this->hostMessageGroup = hostMessageGroup2;
    hostMessageGroup_arraysize = newSize;
}

unsigned int obsMessage::getSourceAdd() const
{
    return this->sourceAdd;
}

void obsMessage::setSourceAdd(unsigned int sourceAdd)
{
    this->sourceAdd = sourceAdd;
}

unsigned int obsMessage::getDestinationAdd() const
{
    return this->destinationAdd;
}

void obsMessage::setDestinationAdd(unsigned int destinationAdd)
{
    this->destinationAdd = destinationAdd;
}

unsigned int obsMessage::getTypeOfService() const
{
    return this->typeOfService;
}

void obsMessage::setTypeOfService(unsigned int typeOfService)
{
    this->typeOfService = typeOfService;
}

unsigned int obsMessage::getPayloadLength() const
{
    return this->payloadLength;
}

void obsMessage::setPayloadLength(unsigned int payloadLength)
{
    this->payloadLength = payloadLength;
}

unsigned int obsMessage::getHeaderLength() const
{
    return this->headerLength;
}

void obsMessage::setHeaderLength(unsigned int headerLength)
{
    this->headerLength = headerLength;
}

unsigned int obsMessage::getSignalWavelenght() const
{
    return this->signalWavelenght;
}

void obsMessage::setSignalWavelenght(unsigned int signalWavelenght)
{
    this->signalWavelenght = signalWavelenght;
}

unsigned int obsMessage::getBurstID() const
{
    return this->burstID;
}

void obsMessage::setBurstID(unsigned int burstID)
{
    this->burstID = burstID;
}

class obsMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hostMessageGroup,
        FIELD_sourceAdd,
        FIELD_destinationAdd,
        FIELD_typeOfService,
        FIELD_payloadLength,
        FIELD_headerLength,
        FIELD_signalWavelenght,
        FIELD_burstID,
    };
  public:
    obsMessageDescriptor();
    virtual ~obsMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(obsMessageDescriptor)

obsMessageDescriptor::obsMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(obsMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

obsMessageDescriptor::~obsMessageDescriptor()
{
    delete[] propertyNames;
}

bool obsMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<obsMessage *>(obj)!=nullptr;
}

const char **obsMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *obsMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int obsMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int obsMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_hostMessageGroup
        FD_ISEDITABLE,    // FIELD_sourceAdd
        FD_ISEDITABLE,    // FIELD_destinationAdd
        FD_ISEDITABLE,    // FIELD_typeOfService
        FD_ISEDITABLE,    // FIELD_payloadLength
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_signalWavelenght
        FD_ISEDITABLE,    // FIELD_burstID
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *obsMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hostMessageGroup",
        "sourceAdd",
        "destinationAdd",
        "typeOfService",
        "payloadLength",
        "headerLength",
        "signalWavelenght",
        "burstID",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int obsMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hostMessageGroup") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceAdd") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "destinationAdd") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "typeOfService") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "payloadLength") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "signalWavelenght") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "burstID") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *obsMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "hostMessage",    // FIELD_hostMessageGroup
        "unsigned int",    // FIELD_sourceAdd
        "unsigned int",    // FIELD_destinationAdd
        "unsigned int",    // FIELD_typeOfService
        "unsigned int",    // FIELD_payloadLength
        "unsigned int",    // FIELD_headerLength
        "unsigned int",    // FIELD_signalWavelenght
        "unsigned int",    // FIELD_burstID
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **obsMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *obsMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int obsMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: return pp->getHostMessageGroupArraySize();
        default: return 0;
    }
}

void obsMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: pp->setHostMessageGroupArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'obsMessage'", field);
    }
}

const char *obsMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: { const hostMessage * value = pp->getHostMessageGroup(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string obsMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: { auto obj = pp->getHostMessageGroup(i); return obj == nullptr ? "" : obj->str(); }
        case FIELD_sourceAdd: return ulong2string(pp->getSourceAdd());
        case FIELD_destinationAdd: return ulong2string(pp->getDestinationAdd());
        case FIELD_typeOfService: return ulong2string(pp->getTypeOfService());
        case FIELD_payloadLength: return ulong2string(pp->getPayloadLength());
        case FIELD_headerLength: return ulong2string(pp->getHeaderLength());
        case FIELD_signalWavelenght: return ulong2string(pp->getSignalWavelenght());
        case FIELD_burstID: return ulong2string(pp->getBurstID());
        default: return "";
    }
}

void obsMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAdd: pp->setSourceAdd(string2ulong(value)); break;
        case FIELD_destinationAdd: pp->setDestinationAdd(string2ulong(value)); break;
        case FIELD_typeOfService: pp->setTypeOfService(string2ulong(value)); break;
        case FIELD_payloadLength: pp->setPayloadLength(string2ulong(value)); break;
        case FIELD_headerLength: pp->setHeaderLength(string2ulong(value)); break;
        case FIELD_signalWavelenght: pp->setSignalWavelenght(string2ulong(value)); break;
        case FIELD_burstID: pp->setBurstID(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'obsMessage'", field);
    }
}

omnetpp::cValue obsMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: return omnetpp::toAnyPtr(pp->getHostMessageGroup(i)); break;
        case FIELD_sourceAdd: return (omnetpp::intval_t)(pp->getSourceAdd());
        case FIELD_destinationAdd: return (omnetpp::intval_t)(pp->getDestinationAdd());
        case FIELD_typeOfService: return (omnetpp::intval_t)(pp->getTypeOfService());
        case FIELD_payloadLength: return (omnetpp::intval_t)(pp->getPayloadLength());
        case FIELD_headerLength: return (omnetpp::intval_t)(pp->getHeaderLength());
        case FIELD_signalWavelenght: return (omnetpp::intval_t)(pp->getSignalWavelenght());
        case FIELD_burstID: return (omnetpp::intval_t)(pp->getBurstID());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'obsMessage' as cValue -- field index out of range?", field);
    }
}

void obsMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: pp->setHostMessageGroup(i,omnetpp::fromAnyPtr<hostMessage>(value.pointerValue())); break;
        case FIELD_sourceAdd: pp->setSourceAdd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_destinationAdd: pp->setDestinationAdd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_typeOfService: pp->setTypeOfService(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_payloadLength: pp->setPayloadLength(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_headerLength: pp->setHeaderLength(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_signalWavelenght: pp->setSignalWavelenght(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_burstID: pp->setBurstID(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'obsMessage'", field);
    }
}

const char *obsMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_hostMessageGroup: return omnetpp::opp_typename(typeid(hostMessage));
        default: return nullptr;
    };
}

omnetpp::any_ptr obsMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: return omnetpp::toAnyPtr(pp->getHostMessageGroup(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void obsMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    obsMessage *pp = omnetpp::fromAnyPtr<obsMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hostMessageGroup: pp->setHostMessageGroup(i,omnetpp::fromAnyPtr<hostMessage>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'obsMessage'", field);
    }
}

Register_Class(resourceRequest)

resourceRequest::resourceRequest(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

resourceRequest::resourceRequest(const resourceRequest& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

resourceRequest::~resourceRequest()
{
}

resourceRequest& resourceRequest::operator=(const resourceRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void resourceRequest::copy(const resourceRequest& other)
{
    this->typeOfMsg = other.typeOfMsg;
    this->generationTime = other.generationTime;
    this->resourceDelay = other.resourceDelay;
    this->sourceNode = other.sourceNode;
    this->destinationNode = other.destinationNode;
    this->signalWavelenght = other.signalWavelenght;
    this->burstID = other.burstID;
    this->typeOfService = other.typeOfService;
}

void resourceRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->typeOfMsg);
    doParsimPacking(b,this->generationTime);
    doParsimPacking(b,this->resourceDelay);
    doParsimPacking(b,this->sourceNode);
    doParsimPacking(b,this->destinationNode);
    doParsimPacking(b,this->signalWavelenght);
    doParsimPacking(b,this->burstID);
    doParsimPacking(b,this->typeOfService);
}

void resourceRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->typeOfMsg);
    doParsimUnpacking(b,this->generationTime);
    doParsimUnpacking(b,this->resourceDelay);
    doParsimUnpacking(b,this->sourceNode);
    doParsimUnpacking(b,this->destinationNode);
    doParsimUnpacking(b,this->signalWavelenght);
    doParsimUnpacking(b,this->burstID);
    doParsimUnpacking(b,this->typeOfService);
}

unsigned int resourceRequest::getTypeOfMsg() const
{
    return this->typeOfMsg;
}

void resourceRequest::setTypeOfMsg(unsigned int typeOfMsg)
{
    this->typeOfMsg = typeOfMsg;
}

double resourceRequest::getGenerationTime() const
{
    return this->generationTime;
}

void resourceRequest::setGenerationTime(double generationTime)
{
    this->generationTime = generationTime;
}

double resourceRequest::getResourceDelay() const
{
    return this->resourceDelay;
}

void resourceRequest::setResourceDelay(double resourceDelay)
{
    this->resourceDelay = resourceDelay;
}

unsigned int resourceRequest::getSourceNode() const
{
    return this->sourceNode;
}

void resourceRequest::setSourceNode(unsigned int sourceNode)
{
    this->sourceNode = sourceNode;
}

unsigned int resourceRequest::getDestinationNode() const
{
    return this->destinationNode;
}

void resourceRequest::setDestinationNode(unsigned int destinationNode)
{
    this->destinationNode = destinationNode;
}

unsigned int resourceRequest::getSignalWavelenght() const
{
    return this->signalWavelenght;
}

void resourceRequest::setSignalWavelenght(unsigned int signalWavelenght)
{
    this->signalWavelenght = signalWavelenght;
}

unsigned int resourceRequest::getBurstID() const
{
    return this->burstID;
}

void resourceRequest::setBurstID(unsigned int burstID)
{
    this->burstID = burstID;
}

unsigned int resourceRequest::getTypeOfService() const
{
    return this->typeOfService;
}

void resourceRequest::setTypeOfService(unsigned int typeOfService)
{
    this->typeOfService = typeOfService;
}

class resourceRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_typeOfMsg,
        FIELD_generationTime,
        FIELD_resourceDelay,
        FIELD_sourceNode,
        FIELD_destinationNode,
        FIELD_signalWavelenght,
        FIELD_burstID,
        FIELD_typeOfService,
    };
  public:
    resourceRequestDescriptor();
    virtual ~resourceRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(resourceRequestDescriptor)

resourceRequestDescriptor::resourceRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(resourceRequest)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

resourceRequestDescriptor::~resourceRequestDescriptor()
{
    delete[] propertyNames;
}

bool resourceRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<resourceRequest *>(obj)!=nullptr;
}

const char **resourceRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *resourceRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int resourceRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int resourceRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_typeOfMsg
        FD_ISEDITABLE,    // FIELD_generationTime
        FD_ISEDITABLE,    // FIELD_resourceDelay
        FD_ISEDITABLE,    // FIELD_sourceNode
        FD_ISEDITABLE,    // FIELD_destinationNode
        FD_ISEDITABLE,    // FIELD_signalWavelenght
        FD_ISEDITABLE,    // FIELD_burstID
        FD_ISEDITABLE,    // FIELD_typeOfService
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *resourceRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "typeOfMsg",
        "generationTime",
        "resourceDelay",
        "sourceNode",
        "destinationNode",
        "signalWavelenght",
        "burstID",
        "typeOfService",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int resourceRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "typeOfMsg") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "generationTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "resourceDelay") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sourceNode") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "destinationNode") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "signalWavelenght") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "burstID") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "typeOfService") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *resourceRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_typeOfMsg
        "double",    // FIELD_generationTime
        "double",    // FIELD_resourceDelay
        "unsigned int",    // FIELD_sourceNode
        "unsigned int",    // FIELD_destinationNode
        "unsigned int",    // FIELD_signalWavelenght
        "unsigned int",    // FIELD_burstID
        "unsigned int",    // FIELD_typeOfService
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **resourceRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *resourceRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int resourceRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void resourceRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'resourceRequest'", field);
    }
}

const char *resourceRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string resourceRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: return ulong2string(pp->getTypeOfMsg());
        case FIELD_generationTime: return double2string(pp->getGenerationTime());
        case FIELD_resourceDelay: return double2string(pp->getResourceDelay());
        case FIELD_sourceNode: return ulong2string(pp->getSourceNode());
        case FIELD_destinationNode: return ulong2string(pp->getDestinationNode());
        case FIELD_signalWavelenght: return ulong2string(pp->getSignalWavelenght());
        case FIELD_burstID: return ulong2string(pp->getBurstID());
        case FIELD_typeOfService: return ulong2string(pp->getTypeOfService());
        default: return "";
    }
}

void resourceRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: pp->setTypeOfMsg(string2ulong(value)); break;
        case FIELD_generationTime: pp->setGenerationTime(string2double(value)); break;
        case FIELD_resourceDelay: pp->setResourceDelay(string2double(value)); break;
        case FIELD_sourceNode: pp->setSourceNode(string2ulong(value)); break;
        case FIELD_destinationNode: pp->setDestinationNode(string2ulong(value)); break;
        case FIELD_signalWavelenght: pp->setSignalWavelenght(string2ulong(value)); break;
        case FIELD_burstID: pp->setBurstID(string2ulong(value)); break;
        case FIELD_typeOfService: pp->setTypeOfService(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'resourceRequest'", field);
    }
}

omnetpp::cValue resourceRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: return (omnetpp::intval_t)(pp->getTypeOfMsg());
        case FIELD_generationTime: return pp->getGenerationTime();
        case FIELD_resourceDelay: return pp->getResourceDelay();
        case FIELD_sourceNode: return (omnetpp::intval_t)(pp->getSourceNode());
        case FIELD_destinationNode: return (omnetpp::intval_t)(pp->getDestinationNode());
        case FIELD_signalWavelenght: return (omnetpp::intval_t)(pp->getSignalWavelenght());
        case FIELD_burstID: return (omnetpp::intval_t)(pp->getBurstID());
        case FIELD_typeOfService: return (omnetpp::intval_t)(pp->getTypeOfService());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'resourceRequest' as cValue -- field index out of range?", field);
    }
}

void resourceRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: pp->setTypeOfMsg(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_generationTime: pp->setGenerationTime(value.doubleValue()); break;
        case FIELD_resourceDelay: pp->setResourceDelay(value.doubleValue()); break;
        case FIELD_sourceNode: pp->setSourceNode(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_destinationNode: pp->setDestinationNode(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_signalWavelenght: pp->setSignalWavelenght(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_burstID: pp->setBurstID(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_typeOfService: pp->setTypeOfService(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'resourceRequest'", field);
    }
}

const char *resourceRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr resourceRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void resourceRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    resourceRequest *pp = omnetpp::fromAnyPtr<resourceRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'resourceRequest'", field);
    }
}

Register_Class(configurationMessage)

configurationMessage::configurationMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

configurationMessage::configurationMessage(const configurationMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

configurationMessage::~configurationMessage()
{
}

configurationMessage& configurationMessage::operator=(const configurationMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void configurationMessage::copy(const configurationMessage& other)
{
    this->typeOfMsg = other.typeOfMsg;
    this->destinationNode = other.destinationNode;
    this->inputTrafficPort = other.inputTrafficPort;
    this->outputTrafficPort = other.outputTrafficPort;
    this->numberOfNodes = other.numberOfNodes;
    this->signalWavelenght = other.signalWavelenght;
    this->burstID = other.burstID;
    this->delayAI = other.delayAI;
    this->requestGenerationDelay = other.requestGenerationDelay;
    this->configurationDelay = other.configurationDelay;
}

void configurationMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->typeOfMsg);
    doParsimPacking(b,this->destinationNode);
    doParsimPacking(b,this->inputTrafficPort);
    doParsimPacking(b,this->outputTrafficPort);
    doParsimPacking(b,this->numberOfNodes);
    doParsimPacking(b,this->signalWavelenght);
    doParsimPacking(b,this->burstID);
    doParsimPacking(b,this->delayAI);
    doParsimPacking(b,this->requestGenerationDelay);
    doParsimPacking(b,this->configurationDelay);
}

void configurationMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->typeOfMsg);
    doParsimUnpacking(b,this->destinationNode);
    doParsimUnpacking(b,this->inputTrafficPort);
    doParsimUnpacking(b,this->outputTrafficPort);
    doParsimUnpacking(b,this->numberOfNodes);
    doParsimUnpacking(b,this->signalWavelenght);
    doParsimUnpacking(b,this->burstID);
    doParsimUnpacking(b,this->delayAI);
    doParsimUnpacking(b,this->requestGenerationDelay);
    doParsimUnpacking(b,this->configurationDelay);
}

unsigned int configurationMessage::getTypeOfMsg() const
{
    return this->typeOfMsg;
}

void configurationMessage::setTypeOfMsg(unsigned int typeOfMsg)
{
    this->typeOfMsg = typeOfMsg;
}

unsigned int configurationMessage::getDestinationNode() const
{
    return this->destinationNode;
}

void configurationMessage::setDestinationNode(unsigned int destinationNode)
{
    this->destinationNode = destinationNode;
}

unsigned int configurationMessage::getInputTrafficPort() const
{
    return this->inputTrafficPort;
}

void configurationMessage::setInputTrafficPort(unsigned int inputTrafficPort)
{
    this->inputTrafficPort = inputTrafficPort;
}

unsigned int configurationMessage::getOutputTrafficPort() const
{
    return this->outputTrafficPort;
}

void configurationMessage::setOutputTrafficPort(unsigned int outputTrafficPort)
{
    this->outputTrafficPort = outputTrafficPort;
}

unsigned int configurationMessage::getNumberOfNodes() const
{
    return this->numberOfNodes;
}

void configurationMessage::setNumberOfNodes(unsigned int numberOfNodes)
{
    this->numberOfNodes = numberOfNodes;
}

unsigned int configurationMessage::getSignalWavelenght() const
{
    return this->signalWavelenght;
}

void configurationMessage::setSignalWavelenght(unsigned int signalWavelenght)
{
    this->signalWavelenght = signalWavelenght;
}

unsigned int configurationMessage::getBurstID() const
{
    return this->burstID;
}

void configurationMessage::setBurstID(unsigned int burstID)
{
    this->burstID = burstID;
}

double configurationMessage::getDelayAI() const
{
    return this->delayAI;
}

void configurationMessage::setDelayAI(double delayAI)
{
    this->delayAI = delayAI;
}

double configurationMessage::getRequestGenerationDelay() const
{
    return this->requestGenerationDelay;
}

void configurationMessage::setRequestGenerationDelay(double requestGenerationDelay)
{
    this->requestGenerationDelay = requestGenerationDelay;
}

double configurationMessage::getConfigurationDelay() const
{
    return this->configurationDelay;
}

void configurationMessage::setConfigurationDelay(double configurationDelay)
{
    this->configurationDelay = configurationDelay;
}

class configurationMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_typeOfMsg,
        FIELD_destinationNode,
        FIELD_inputTrafficPort,
        FIELD_outputTrafficPort,
        FIELD_numberOfNodes,
        FIELD_signalWavelenght,
        FIELD_burstID,
        FIELD_delayAI,
        FIELD_requestGenerationDelay,
        FIELD_configurationDelay,
    };
  public:
    configurationMessageDescriptor();
    virtual ~configurationMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(configurationMessageDescriptor)

configurationMessageDescriptor::configurationMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(configurationMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

configurationMessageDescriptor::~configurationMessageDescriptor()
{
    delete[] propertyNames;
}

bool configurationMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<configurationMessage *>(obj)!=nullptr;
}

const char **configurationMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *configurationMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int configurationMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int configurationMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_typeOfMsg
        FD_ISEDITABLE,    // FIELD_destinationNode
        FD_ISEDITABLE,    // FIELD_inputTrafficPort
        FD_ISEDITABLE,    // FIELD_outputTrafficPort
        FD_ISEDITABLE,    // FIELD_numberOfNodes
        FD_ISEDITABLE,    // FIELD_signalWavelenght
        FD_ISEDITABLE,    // FIELD_burstID
        FD_ISEDITABLE,    // FIELD_delayAI
        FD_ISEDITABLE,    // FIELD_requestGenerationDelay
        FD_ISEDITABLE,    // FIELD_configurationDelay
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *configurationMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "typeOfMsg",
        "destinationNode",
        "inputTrafficPort",
        "outputTrafficPort",
        "numberOfNodes",
        "signalWavelenght",
        "burstID",
        "delayAI",
        "requestGenerationDelay",
        "configurationDelay",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int configurationMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "typeOfMsg") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destinationNode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "inputTrafficPort") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "outputTrafficPort") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "numberOfNodes") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "signalWavelenght") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "burstID") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "delayAI") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "requestGenerationDelay") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "configurationDelay") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *configurationMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_typeOfMsg
        "unsigned int",    // FIELD_destinationNode
        "unsigned int",    // FIELD_inputTrafficPort
        "unsigned int",    // FIELD_outputTrafficPort
        "unsigned int",    // FIELD_numberOfNodes
        "unsigned int",    // FIELD_signalWavelenght
        "unsigned int",    // FIELD_burstID
        "double",    // FIELD_delayAI
        "double",    // FIELD_requestGenerationDelay
        "double",    // FIELD_configurationDelay
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **configurationMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *configurationMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int configurationMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void configurationMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'configurationMessage'", field);
    }
}

const char *configurationMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string configurationMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: return ulong2string(pp->getTypeOfMsg());
        case FIELD_destinationNode: return ulong2string(pp->getDestinationNode());
        case FIELD_inputTrafficPort: return ulong2string(pp->getInputTrafficPort());
        case FIELD_outputTrafficPort: return ulong2string(pp->getOutputTrafficPort());
        case FIELD_numberOfNodes: return ulong2string(pp->getNumberOfNodes());
        case FIELD_signalWavelenght: return ulong2string(pp->getSignalWavelenght());
        case FIELD_burstID: return ulong2string(pp->getBurstID());
        case FIELD_delayAI: return double2string(pp->getDelayAI());
        case FIELD_requestGenerationDelay: return double2string(pp->getRequestGenerationDelay());
        case FIELD_configurationDelay: return double2string(pp->getConfigurationDelay());
        default: return "";
    }
}

void configurationMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: pp->setTypeOfMsg(string2ulong(value)); break;
        case FIELD_destinationNode: pp->setDestinationNode(string2ulong(value)); break;
        case FIELD_inputTrafficPort: pp->setInputTrafficPort(string2ulong(value)); break;
        case FIELD_outputTrafficPort: pp->setOutputTrafficPort(string2ulong(value)); break;
        case FIELD_numberOfNodes: pp->setNumberOfNodes(string2ulong(value)); break;
        case FIELD_signalWavelenght: pp->setSignalWavelenght(string2ulong(value)); break;
        case FIELD_burstID: pp->setBurstID(string2ulong(value)); break;
        case FIELD_delayAI: pp->setDelayAI(string2double(value)); break;
        case FIELD_requestGenerationDelay: pp->setRequestGenerationDelay(string2double(value)); break;
        case FIELD_configurationDelay: pp->setConfigurationDelay(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'configurationMessage'", field);
    }
}

omnetpp::cValue configurationMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: return (omnetpp::intval_t)(pp->getTypeOfMsg());
        case FIELD_destinationNode: return (omnetpp::intval_t)(pp->getDestinationNode());
        case FIELD_inputTrafficPort: return (omnetpp::intval_t)(pp->getInputTrafficPort());
        case FIELD_outputTrafficPort: return (omnetpp::intval_t)(pp->getOutputTrafficPort());
        case FIELD_numberOfNodes: return (omnetpp::intval_t)(pp->getNumberOfNodes());
        case FIELD_signalWavelenght: return (omnetpp::intval_t)(pp->getSignalWavelenght());
        case FIELD_burstID: return (omnetpp::intval_t)(pp->getBurstID());
        case FIELD_delayAI: return pp->getDelayAI();
        case FIELD_requestGenerationDelay: return pp->getRequestGenerationDelay();
        case FIELD_configurationDelay: return pp->getConfigurationDelay();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'configurationMessage' as cValue -- field index out of range?", field);
    }
}

void configurationMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        case FIELD_typeOfMsg: pp->setTypeOfMsg(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_destinationNode: pp->setDestinationNode(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_inputTrafficPort: pp->setInputTrafficPort(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_outputTrafficPort: pp->setOutputTrafficPort(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_numberOfNodes: pp->setNumberOfNodes(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_signalWavelenght: pp->setSignalWavelenght(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_burstID: pp->setBurstID(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_delayAI: pp->setDelayAI(value.doubleValue()); break;
        case FIELD_requestGenerationDelay: pp->setRequestGenerationDelay(value.doubleValue()); break;
        case FIELD_configurationDelay: pp->setConfigurationDelay(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'configurationMessage'", field);
    }
}

const char *configurationMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr configurationMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void configurationMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    configurationMessage *pp = omnetpp::fromAnyPtr<configurationMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'configurationMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

