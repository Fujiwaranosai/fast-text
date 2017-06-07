

#include "classifierWorker.h"
#include <v8.h>

void ClassifierWorker::Execute () {
    try {
        wrapper_->loadModel();
        result_ = wrapper_->predict(sentence_, k_);
    } catch (std::string errorMessage) {
        SetErrorMessage(errorMessage.c_str());
    }
}


void ClassifierWorker::HandleErrorCallback () {
    Nan::HandleScope scope;

    v8::Local<v8::Value> argv[] = {
        Nan::Error(ErrorMessage()),
        Nan::Null()
    };

    callback->Call(2, argv);
}

void ClassifierWorker::HandleOKCallback () {
    Nan::HandleScope scope;
    v8::Local<v8::Array> result = Nan::New<v8::Array>(result_.size());

    for(uint32_t i = 0; i < result_.size(); i++) {
        v8::Local<v8::Object> returnObject = Nan::New<v8::Object>();

        returnObject->Set(
            Nan::New<v8::String>("label").ToLocalChecked(),
            Nan::New<v8::String>(result_[i].label.c_str()).ToLocalChecked()
        );

        returnObject->Set(
            Nan::New<v8::String>("value").ToLocalChecked(),
            Nan::New<v8::Number>(result_[i].value)
        );

        result->Set(i, returnObject);
    }

    v8::Local<v8::Value> argv[] = {
        Nan::Null(),
        result
    };

    callback->Call(2, argv);
}