#include "SubjectImpl.h"
#include "NotifHandler.h"
#include "global.h"

SubjectImpl::SubjectImpl() : m_nNotifyInProg(0), m_bCleanObserverList(false) {}

SubjectImpl::SubjectImpl(const Name& nm, const std::weak_ptr<ISubject>& subj)
    : m_name(nm),
      m_subj(subj),
      m_nNotifyInProg(0),
      m_bCleanObserverList(false) {}

SubjectImpl::~SubjectImpl() {}

void SubjectImpl::Subscribe(const std::weak_ptr<IObserver>& obs, int reason) {
  if (!IsSubscribed(obs, reason) && !IsSubscribed(obs, REASON_ALL)) {
    if (m_nNotifyInProg) {
      m_listPendingSubscribers.push_back(std::make_pair(obs, reason));
      m_bCleanObserverList = true;
    } else {
      m_mapObserverLists[reason].push_back(obs);
    }
  }

  if (!m_nNotifyInProg) {
    for (auto& key : m_mapObserverLists) {
      ObserverList& obsList = key.second;
      RmoveBrokenPointers(obsList);
    }
  }
}

void SubjectImpl::Unsubscribe(const std::weak_ptr<IObserver>& obs, int reason) {
  if (reason == REASON_ALL) {
    for (auto& key : m_mapObserverLists) {
      RemoveObserver(obs, key.first);
    }
  } else {
    RemoveObserver(obs, reason);
  }
}

void SubjectImpl::Update(const Any val[], int narg, int reason) {
  INotificationHandler::Instance()->Update(weak_from_this(), val, narg, reason);
}

void SubjectImpl::Update(const Any& val, int reason) {
  Update(&val, 1, reason);
}

void SubjectImpl::UpdateImmediate(const Any val[], int narg, int reason) {
  // implement after
}

void SubjectImpl::UpdateAsync(const Any& val, int reason) {
  UpdateAsync(&val, 1, reason);
}

void SubjectImpl::UpdateAsync(const Any val[], int narg, int reason) {
  INotificationHandler::Instance()->UpdateAsync(weak_from_this(), val, narg,
                                                reason);
}

bool SubjectImpl::IsSubscribed(const std::weak_ptr<IObserver>& obs,
                               int reason) {
  auto obsList = m_mapObserverLists.find(reason);
  if (obsList != m_mapObserverLists.end()) {
    return std::find(obsList->second.begin(), obsList->second.end(), obs) !=
           obsList->second.end();
  }

  return false;
}

void SubjectImpl::RemoveObserver(const std::weak_ptr<IObserver>& obs,
                                 int reason) {
  auto obsList = m_mapObserverLists.find(reason);
  if (obsList != m_mapObserverLists.end()) {
    if (m_nNotifyInProg == 0) {
      obsList->second.remove(obs);
    } else {
      auto isEnd =
          std::find(obsList->second.begin(), obsList->second.end(), obs);
      if (isEnd != obsList->second.end()) {
        isEnd->reset();
      }
      m_bCleanObserverList = true;
    }
  }
}

void SubjectImpl::NotifyList(ObserverList& obsList, int reason, const Any val[],
                             int narg) {
  if (!obsList.empty()) {

  }
}

void SubjectImpl::RmoveBrokenPointers(ObserverList& obs) {}
