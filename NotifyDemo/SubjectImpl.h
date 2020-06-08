#pragma once
#include "ISubjectImpl.h"
#include "Name.h"

class SubjectImpl : public ISubjectImpl {
public:
  SubjectImpl();
  SubjectImpl(const Name& nm, const std::weak_ptr<ISubject>& subj);

  virtual ~SubjectImpl();

  void Subscribe(const std::weak_ptr<IObserver>& obs, int reason);
  void Unsubscribe(const std::weak_ptr<IObserver>& obs, int reason);

  ISubjectImpl* GetSubjectImpl() {
    return this;
  }

  void Update(const Any val[], int narg, int reason) override;
  void Update(const Any& val, int reason) override;
  void Update(const Any val[], int narg, int reason) override;
  void UpdateImmediate(const Any val[], int narg, int reason) override;
  void UpdateAsync(const Any& val, int reason) override;
  void UpdateAsync(const Any val[], int narg, int reason) override;

  Name GetName() const;
  
private:

  Name m_name;
};
