#include "NotifHandler.h"

namespace {
std::unique_ptr<INotificationHandler> g_notifHandlerInstance(nullptr);
}

std::unique_ptr<INotificationHandler>& INotificationHandler::Instance() {
  if (!g_notifHandlerInstance) {
    g_notifHandlerInstance = std::make_unique<NotifHandler>();
  }
  return g_notifHandlerInstance;
}







