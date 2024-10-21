
#include <nan.h>
#include "classifier.h"   // NOLINT(build/include)
#include "query.h"   // NOLINT(build/include)

NAN_MODULE_INIT(Init) {
  Classifier::Init(target);
  Query::Init(target);
}

NAN_MODULE_WORKER_ENABLED(myaddon, Init)
