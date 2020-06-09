#pragma once
#include <memory>
#include <list>
#include "ISubjectImpl.h"

class INotificationHandler {
 public:
  static std::unique_ptr<INotificationHandler>& Instance();


  /// This is the operation that SubjectImpl should use to
  /// request notification.  The NotificationHandler will
  /// determine whether to perform the notification synchronously
  /// or asynchronously.
  virtual void Update(const std::weak_ptr<ISubjectImpl>& subjImpl,
                      const Any val[],
                      int narg, int reason) = 0;

  /// Explicitly request asynchronous notification.  The
  /// notification handler will post a message to the IMessageDispatcher
  /// to be handled in a later application cycle.  IMessageDispatcher
  /// will then dispatch the message back to the INotificationHandler for
  /// normal Update semantics.
  virtual void UpdateAsync(const std::weak_ptr<ISubjectImpl>& subjImpl,
                           const Any val[],
                           int narg, int reason) = 0;

  /// Explicitly request synchronous notification.  Note that
  /// this request for synchronicity is only a hint to the
  /// INotificationHandler.  If the calling thread is not
  /// the thread with notification "affinity", the update
  /// will still be performed asynchronously (see UpdateAsync).
  virtual void UpdateSync(const std::weak_ptr<ISubjectImpl>& subjImpl,
                          const Any val[],
                          int narg, int reason) = 0;

  /// Required for asnychronous notifications.
  /// Returns whether there are more notifications in the queue still to
  /// process. If doall is set, then all notifications will be processed,
  /// otherwise, only the ones that were in the queue to start out with will be
  /// processed.
  virtual bool ProcessUpdateQueue(bool doall) = 0;

  /// required for ISubjectImpl's
  virtual void QueueUpdate(const std::weak_ptr<ISubjectImpl>& pSubj,
                           int reason,
                           const Any change[], int narg, const std::list<std::weak_ptr<IObserver> >& listObs) = 0;

  virtual size_t UpdateQueueSize() const = 0;
};