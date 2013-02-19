/*
 * See Copyright Notice in qnode.h
 */

#ifndef __QSERVER_H__
#define __QSERVER_H__

#include "qconfig.h"
#include "qidmap.h"
#include "qmutex.h"
#include "qtype.h"

#define QSERVER_THREAD_TID 0

struct qactor_t;
struct qdescriptor_t;
struct qengine_t;
struct qevent_t;
struct qthread_t;
struct qmailbox_t;
struct qmsg_t;
 
enum {
  STOPPED   = 0,
  RUNNING   = 1,
  STOPPING  = 2,
};

typedef struct qserver_t {
  struct qconfig_t      *config;
  struct qengine_t      *engine;
  struct qthread_t      **threads;
  struct qmailbox_t     **in_box;
  struct qmailbox_t     **out_box;
  struct qthread_log_t  **thread_log;
  struct qactor_t       **actors;
  struct qdescriptor_t  **descriptors;
  unsigned int          num_actor;
  qidmap_t              id_map;
  qmutex_t              id_map_mutex;
  int                   status;
} qserver_t;

int qserver_run(struct qconfig_t *config);

void qserver_new_actor(struct qactor_t *actor);

qtid_t qserver_worker_thread();

struct qactor_t* qserver_get_actor(qid_t id);

/* the GLOBAL server in the system */
extern struct qserver_t *g_server;

#endif  /* __QSERVER_H__ */
