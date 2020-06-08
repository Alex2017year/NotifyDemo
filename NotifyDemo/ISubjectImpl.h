#pragma once
#include "ISubject.h"
#include <memory>
class Any;
class Name;

class ISubjectImpl : public ISubject {
public:
  virtual void Update(const Any& val, int reason) = 0;
  virtual void Update(const Any val[], int narg, int reason) = 0;
  virtual void UpdateImmediate(const Any val[], int narg, int reason) = 0;
  virtual void UpdateAsync(const Any& val, int reason) = 0;
  virtual void UpdateAsync(const Any val[], int narg, int reason) = 0;
};

class AggSubjImpl {
public:
  AggSubjImpl();
  ~AggSubjImpl();

  AggSubjImpl(std::weak_ptr<ISubject> subj, const Name& nm);

  ISubjectImpl* operator->();

private:
  std::unique_ptr<ISubjectImpl> m_impl;
};

