const addon = require('../../build/Release/nodegui_plugin_metrics.node');
const { QRect } = require('@nodegui/nodegui');

class QFontMetrics {
	constructor(font) {
		this.native = new addon.QFontMetrics(font.native);
	}

	boundingRect(...args) {
		return new QRect(this.native.boundingRect(...args));
	}

	elidedText(...args){
		return this.native.elidedText(...args);
	}
}

module.exports = QFontMetrics;
