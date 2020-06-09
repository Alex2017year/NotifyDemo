#pragma once
#include "ISubjectImpl.h"
#include "Name.h"

#include <memory>
#include <list>
#include <map>
#include <utility>

class SubjectImpl : public ISubjectImpl,
                    public std::enable_shared_from_this<SubjectImpl> {
 public:
  SubjectImpl();
  SubjectImpl(const Name& nm, const std::weak_ptr<ISubject>& subj);

  virtual ~SubjectImpl();

  void Subscribe(const std::weak_ptr<IObserver>& obs, int reason) override;
  void Unsubscribe(const std::weak_ptr<IObserver>& obs, int reason) override;

  ISubjectImpl* GetSubjectImpl() {
    return this;
  }

  void Update(const Any val[], int narg, int reason) override;
  void Update(const Any& val, int reason) override;
  void UpdateImmediate(const Any val[], int narg, int reason) override;
  void UpdateAsync(const Any& val, int reason) override;
  void UpdateAsync(const Any val[], int narg, int reason) override;

  Name GetName() const { return m_name; }

private:  
  Name m_name;

  // 数据结构的设计
  // eventId <---> list<IObserver>
  typedef std::list<std::weak_ptr<IObserver>> ObserverList;
  typedef std::map<int, ObserverList> SubscriptionLists;
  SubscriptionLists m_mapObserverLists;

  // this is used for observers that subscribe during notification
  // pending: list(<IObserver<->eventId>)
  typedef std::pair<std::weak_ptr<IObserver>, int> Pending;
  typedef std::list<Pending> PendingList;
  PendingList m_listPendingSubscribers;

  int m_nNotifyInProg;
  bool m_bCleanObserverList;

  std::weak_ptr<ISubject> m_subj;

private:
  bool IsSubscribed(const std::weak_ptr<IObserver>& obs, int reason);
  void RemoveObserver(const std::weak_ptr<IObserver>& obs, int reason);
  void NotifyList(ObserverList& obsList, int reason, const Any val[], int narg);
  void RmoveBrokenPointers(ObserverList& obs);
};
