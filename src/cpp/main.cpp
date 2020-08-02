#include <napi.h>
#include "QFontMetrics/qfontmetrics_wrap.h"

Napi::Object Main(Napi::Env env, Napi::Object exports) {
	QFontMetricsWrap::init(env, exports);
	return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
