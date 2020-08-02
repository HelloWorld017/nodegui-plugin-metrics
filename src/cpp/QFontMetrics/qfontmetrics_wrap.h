#pragma once
#include <napi.h>
#include <nodegui/Extras/Utils/nutils.h>
#include <QFontMetrics>

class QFontMetricsWrap : public Napi::ObjectWrap<QFontMetricsWrap> {
	private:
		std::unique_ptr<QFontMetrics> instance;

	public:
		static Napi::Object init(Napi::Env env, Napi::Object exports);
		QFontMetricsWrap(const Napi::CallbackInfo &info);
		~QFontMetricsWrap();
		QFontMetrics *getInternalInstance();
		static Napi::FunctionReference constructor;

		Napi::Value boundingRect(const Napi::CallbackInfo &info);
		Napi::Value elidedText(const Napi::CallbackInfo &info);
};
