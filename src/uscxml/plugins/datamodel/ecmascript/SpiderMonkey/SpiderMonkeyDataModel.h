/**
 *  @file
 *  @author     2012-2014 Stefan Radomski (stefan.radomski@cs.tu-darmstadt.de)
 *  @copyright  Simplified BSD
 *
 *  @cond
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the FreeBSD license as published by the FreeBSD
 *  project.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the FreeBSD license along with this
 *  program. If not, see <http://www.opensource.org/licenses/bsd-license>.
 *  @endcond
 */

#ifndef SPIDERMONKEYDATAMODEL_H_88841EE2
#define SPIDERMONKEYDATAMODEL_H_88841EE2

#include "uscxml/Interpreter.h"
#include <list>
#include "jsapi.h"

#ifdef BUILD_AS_PLUGINS
#include "uscxml/plugins/Plugins.h"
#endif

namespace uscxml {
class Event;
class Data;
}

namespace uscxml {

class SpiderMonkeyDataModel : public DataModelImpl {
public:
	SpiderMonkeyDataModel();
	virtual ~SpiderMonkeyDataModel();
	virtual boost::shared_ptr<DataModelImpl> create(InterpreterImpl* interpreter);

	virtual std::list<std::string> getNames() {
		std::list<std::string> names;
		names.push_back("ecmascript");
		return names;
	}

	virtual void initialize();
	virtual void setEvent(const Event& event);

	virtual bool validate(const std::string& location, const std::string& schema);
	virtual bool isLocation(const std::string& expr);

	virtual uint32_t getLength(const std::string& expr);
	virtual void setForeach(const std::string& item,
	                        const std::string& array,
	                        const std::string& index,
	                        uint32_t iteration);
	virtual void pushContext();
	virtual void popContext();

	virtual void eval(const Arabica::DOM::Element<std::string>& scriptElem,
	                  const std::string& expr);
	virtual void assign(const Arabica::DOM::Element<std::string>& assignElem,
	                    const Arabica::DOM::Node<std::string>& node,
	                    const std::string& content);
	virtual void assign(const std::string& location,
	                    const Data& data);

	virtual void init(const Arabica::DOM::Element<std::string>& dataElem,
	                  const Arabica::DOM::Node<std::string>& node,
	                  const std::string& content);
	virtual void init(const std::string& location,
	                  const Data& data);

	virtual std::string andExpressions(std::list<std::string>);

	virtual Data getStringAsData(const std::string& content);

	virtual bool isDeclared(const std::string& expr);

	virtual std::string evalAsString(const std::string& expr);
	virtual bool evalAsBool(const Arabica::DOM::Element<std::string>& node, const std::string& expr);
	virtual bool evalAsBool(const std::string& expr);
	virtual double evalAsNumber(const std::string& expr);

	static void reportError(JSContext *cx, const char *message, JSErrorReport *report);

protected:

	JSObject* _global;

	JSContext* _jsCtx;
	static JSRuntime* _jsRuntime;
};

#ifdef BUILD_AS_PLUGINS
PLUMA_INHERIT_PROVIDER(SpiderMonkeyDataModel, DataModelImpl);
#endif

}

#endif /* end of include guard: SPIDERMONKEYDATAMODEL_H_88841EE2 */
