//
// Generated file, do not edit! Created by opp_msgtool 6.0 from arrivalMsg.msg.
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
#include "arrivalMsg_m.h"

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

Register_Class(ArrivalMsg)

ArrivalMsg::ArrivalMsg(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

ArrivalMsg::ArrivalMsg(const ArrivalMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

ArrivalMsg::~ArrivalMsg()
{
}

ArrivalMsg& ArrivalMsg::operator=(const ArrivalMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ArrivalMsg::copy(const ArrivalMsg& other)
{
    this->priority = other.priority;
    this->firstTime = other.firstTime;
    this->lastTimeJoinServer = other.lastTimeJoinServer;
    this->lastTimeJoinQueue = other.lastTimeJoinQueue;
    this->queueingTime = other.queueingTime;
    this->passedServiceTime = other.passedServiceTime;
    this->isFirstTime_ = other.isFirstTime_;
}

void ArrivalMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->firstTime);
    doParsimPacking(b,this->lastTimeJoinServer);
    doParsimPacking(b,this->lastTimeJoinQueue);
    doParsimPacking(b,this->queueingTime);
    doParsimPacking(b,this->passedServiceTime);
    doParsimPacking(b,this->isFirstTime_);
}

void ArrivalMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->firstTime);
    doParsimUnpacking(b,this->lastTimeJoinServer);
    doParsimUnpacking(b,this->lastTimeJoinQueue);
    doParsimUnpacking(b,this->queueingTime);
    doParsimUnpacking(b,this->passedServiceTime);
    doParsimUnpacking(b,this->isFirstTime_);
}

int ArrivalMsg::getPriority() const
{
    return this->priority;
}

void ArrivalMsg::setPriority(int priority)
{
    this->priority = priority;
}

omnetpp::simtime_t ArrivalMsg::getFirstTime() const
{
    return this->firstTime;
}

void ArrivalMsg::setFirstTime(omnetpp::simtime_t firstTime)
{
    this->firstTime = firstTime;
}

omnetpp::simtime_t ArrivalMsg::getLastTimeJoinServer() const
{
    return this->lastTimeJoinServer;
}

void ArrivalMsg::setLastTimeJoinServer(omnetpp::simtime_t lastTimeJoinServer)
{
    this->lastTimeJoinServer = lastTimeJoinServer;
}

omnetpp::simtime_t ArrivalMsg::getLastTimeJoinQueue() const
{
    return this->lastTimeJoinQueue;
}

void ArrivalMsg::setLastTimeJoinQueue(omnetpp::simtime_t lastTimeJoinQueue)
{
    this->lastTimeJoinQueue = lastTimeJoinQueue;
}

omnetpp::simtime_t ArrivalMsg::getQueueingTime() const
{
    return this->queueingTime;
}

void ArrivalMsg::setQueueingTime(omnetpp::simtime_t queueingTime)
{
    this->queueingTime = queueingTime;
}

omnetpp::simtime_t ArrivalMsg::getPassedServiceTime() const
{
    return this->passedServiceTime;
}

void ArrivalMsg::setPassedServiceTime(omnetpp::simtime_t passedServiceTime)
{
    this->passedServiceTime = passedServiceTime;
}

bool ArrivalMsg::isFirstTime() const
{
    return this->isFirstTime_;
}

void ArrivalMsg::setIsFirstTime(bool isFirstTime)
{
    this->isFirstTime_ = isFirstTime;
}

class ArrivalMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_priority,
        FIELD_firstTime,
        FIELD_lastTimeJoinServer,
        FIELD_lastTimeJoinQueue,
        FIELD_queueingTime,
        FIELD_passedServiceTime,
        FIELD_isFirstTime,
    };
  public:
    ArrivalMsgDescriptor();
    virtual ~ArrivalMsgDescriptor();

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

Register_ClassDescriptor(ArrivalMsgDescriptor)

ArrivalMsgDescriptor::ArrivalMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ArrivalMsg)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

ArrivalMsgDescriptor::~ArrivalMsgDescriptor()
{
    delete[] propertyNames;
}

bool ArrivalMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ArrivalMsg *>(obj)!=nullptr;
}

const char **ArrivalMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ArrivalMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ArrivalMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int ArrivalMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_priority
        FD_ISEDITABLE,    // FIELD_firstTime
        FD_ISEDITABLE,    // FIELD_lastTimeJoinServer
        FD_ISEDITABLE,    // FIELD_lastTimeJoinQueue
        FD_ISEDITABLE,    // FIELD_queueingTime
        FD_ISEDITABLE,    // FIELD_passedServiceTime
        FD_ISEDITABLE,    // FIELD_isFirstTime
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *ArrivalMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "priority",
        "firstTime",
        "lastTimeJoinServer",
        "lastTimeJoinQueue",
        "queueingTime",
        "passedServiceTime",
        "isFirstTime",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int ArrivalMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "firstTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "lastTimeJoinServer") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "lastTimeJoinQueue") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "queueingTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "passedServiceTime") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "isFirstTime") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *ArrivalMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_priority
        "omnetpp::simtime_t",    // FIELD_firstTime
        "omnetpp::simtime_t",    // FIELD_lastTimeJoinServer
        "omnetpp::simtime_t",    // FIELD_lastTimeJoinQueue
        "omnetpp::simtime_t",    // FIELD_queueingTime
        "omnetpp::simtime_t",    // FIELD_passedServiceTime
        "bool",    // FIELD_isFirstTime
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **ArrivalMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *ArrivalMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ArrivalMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ArrivalMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ArrivalMsg'", field);
    }
}

const char *ArrivalMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ArrivalMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_priority: return long2string(pp->getPriority());
        case FIELD_firstTime: return simtime2string(pp->getFirstTime());
        case FIELD_lastTimeJoinServer: return simtime2string(pp->getLastTimeJoinServer());
        case FIELD_lastTimeJoinQueue: return simtime2string(pp->getLastTimeJoinQueue());
        case FIELD_queueingTime: return simtime2string(pp->getQueueingTime());
        case FIELD_passedServiceTime: return simtime2string(pp->getPassedServiceTime());
        case FIELD_isFirstTime: return bool2string(pp->isFirstTime());
        default: return "";
    }
}

void ArrivalMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_priority: pp->setPriority(string2long(value)); break;
        case FIELD_firstTime: pp->setFirstTime(string2simtime(value)); break;
        case FIELD_lastTimeJoinServer: pp->setLastTimeJoinServer(string2simtime(value)); break;
        case FIELD_lastTimeJoinQueue: pp->setLastTimeJoinQueue(string2simtime(value)); break;
        case FIELD_queueingTime: pp->setQueueingTime(string2simtime(value)); break;
        case FIELD_passedServiceTime: pp->setPassedServiceTime(string2simtime(value)); break;
        case FIELD_isFirstTime: pp->setIsFirstTime(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ArrivalMsg'", field);
    }
}

omnetpp::cValue ArrivalMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_priority: return pp->getPriority();
        case FIELD_firstTime: return pp->getFirstTime().dbl();
        case FIELD_lastTimeJoinServer: return pp->getLastTimeJoinServer().dbl();
        case FIELD_lastTimeJoinQueue: return pp->getLastTimeJoinQueue().dbl();
        case FIELD_queueingTime: return pp->getQueueingTime().dbl();
        case FIELD_passedServiceTime: return pp->getPassedServiceTime().dbl();
        case FIELD_isFirstTime: return pp->isFirstTime();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ArrivalMsg' as cValue -- field index out of range?", field);
    }
}

void ArrivalMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_firstTime: pp->setFirstTime(value.doubleValue()); break;
        case FIELD_lastTimeJoinServer: pp->setLastTimeJoinServer(value.doubleValue()); break;
        case FIELD_lastTimeJoinQueue: pp->setLastTimeJoinQueue(value.doubleValue()); break;
        case FIELD_queueingTime: pp->setQueueingTime(value.doubleValue()); break;
        case FIELD_passedServiceTime: pp->setPassedServiceTime(value.doubleValue()); break;
        case FIELD_isFirstTime: pp->setIsFirstTime(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ArrivalMsg'", field);
    }
}

const char *ArrivalMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ArrivalMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ArrivalMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ArrivalMsg *pp = omnetpp::fromAnyPtr<ArrivalMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ArrivalMsg'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

