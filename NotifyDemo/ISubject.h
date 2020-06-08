#pragma once
#include <memory>

class IObserver;
class ISubjectImpl;

class ISubject {
public:
  virtual void Subscribe(const std::weak_ptr<IObserver>& obs, int reason) = 0;
  virtual void Unsubscribe(const std::weak_ptr<IObserver>& obs, int reason) = 0;
  virtual ISubjectImpl* GetSubjectImpl() = 0;
};

#define DECLARE_ISUBJECT_IMPL(s) \
void Subscribe(const std::weak_ptr<IObserver>& obs, int reason) { s->Subscribe(obs, reason); } \
void Unsubscribe(const std::weak_ptr<IObserver>& obs, int reason) { s->Unsubscribe(obs, reason); } \
std::shared_ptr<ISubjectImpl> GetSubjectImpl() { return s.operator->(); }
