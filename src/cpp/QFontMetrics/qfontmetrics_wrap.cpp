#include "qfontmetrics_wrap.h"

#include <nodegui/QtCore/QRect/qrect_wrap.h>
#include <nodegui/QtGui/QFont/qfont_wrap.h>

#include <QString>

Napi::FunctionReference QFontMetricsWrap::constructor;

Napi::Object QFontMetricsWrap::init(Napi::Env env, Napi::Object exports) {
	Napi::HandleScope scope(env);
	char CLASSNAME[] = "QFontMetrics";
	Napi::Function func = DefineClass(
		env, CLASSNAME,
		{
			InstanceMethod("boundingRect", &QFontMetricsWrap::boundingRect),
			InstanceMethod("elidedText", &QFontMetricsWrap::elidedText)
		}
	);

	constructor = Napi::Persistent(func);
	exports.Set(CLASSNAME, func);
	return exports;
}

QFontMetricsWrap::QFontMetricsWrap(const Napi::CallbackInfo& info)
	: Napi::ObjectWrap<QFontMetricsWrap>(info) {

	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if(info.Length() != 1) {
		Napi::TypeError::New(env, "[QFontMetrics] Invalid Arguments")
			.ThrowAsJavaScriptException();
	} else {
		Napi::Object parentObject = info[0].As<Napi::Object>();
		QFontWrap *parentObjectWrap = Napi::ObjectWrap<QFontWrap>::Unwrap(parentObject);

		this->instance = std::make_unique<QFontMetrics>(*parentObjectWrap->getInternalInstance());
	}
}

QFontMetricsWrap::~QFontMetricsWrap() {
	this->instance.reset();
}

QFontMetrics* QFontMetricsWrap::getInternalInstance() { return this->instance.get(); }

Napi::Value QFontMetricsWrap::boundingRect(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if(info.Length() != 1) {
		Napi::TypeError::New(env, "[QFontMetrics] Invalid Arguments")
			.ThrowAsJavaScriptException();

		return env.Null();
	} else {
		QRect boundingRect = this->instance->boundingRect(
			QString::fromUtf8(info[0].As<Napi::String>().Utf8Value().c_str())
		);

		auto instance = QRectWrap::constructor.New(
			{ Napi::External<QRect>::New(env, new QRect(boundingRect)) }
		);

		return instance;
	}
}

Napi::Value QFontMetricsWrap::elidedText(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if(info.Length() < 3) {
		Napi::TypeError::New(env, "[QFontMetrics] Invalid Arguments")
			.ThrowAsJavaScriptException();

		return env.Null();
	} else {
		std::string text = info[0].As<Napi::String>().Utf8Value();
		Qt::TextElideMode mode = static_cast<Qt::TextElideMode>(
			info[1].As<Napi::Number>().Int32Value()
		);
		int width = info[2].As<Napi::Number>().Int32Value();
		int flags = (
			(info.Length() >= 4) ?
			info[3].As<Napi::Number>().Int32Value() :
			0
		);

		 return Napi::String::New(
		 	env,
		 	this->instance->elidedText(
				QString::fromUtf8(text.c_str()),
				mode,
				width,
				flags
			).toStdString()
		);
	}
}
