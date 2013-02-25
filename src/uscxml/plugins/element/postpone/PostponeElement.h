#ifndef POSTPONEELEMENT_H_WN8EIYYI
#define POSTPONEELEMENT_H_WN8EIYYI

#include <uscxml/Interpreter.h>
#include <list>

#ifdef BUILD_AS_PLUGINS
#include "uscxml/plugins/Plugins.h"
#endif

namespace uscxml {

class PostponeElement : public ExecutableContentImpl {
public:
	PostponeElement() {}
	virtual ~PostponeElement() {}
	boost::shared_ptr<ExecutableContentImpl> create(Interpreter* interpreter);

	std::string getLocalName() {
		return "postpone";
	}

	std::string getNamespace() {
		return "http://www.w3.org/2005/07/scxml";
	}

	bool processChildren() {
		return false;
	}

	void enterElement(const Arabica::DOM::Node<std::string>& node);
	void exitElement(const Arabica::DOM::Node<std::string>& node);

protected:
	// once per interpreter
	class Resubmitter : public InterpreterMonitor {
	public:
		Resubmitter(Interpreter* interpreter) {
			interpreter->addMonitor(this);
		}

		static Resubmitter* getInstance(Interpreter* interpreter);
		static void postpone(const Event& event, std::string until, Interpreter* interpreter);

		// InterpreterMonitor
		void onStableConfiguration(Interpreter* interpreter);
		void afterCompletion(Interpreter* interpreter);

		std::list<std::pair<std::string, Event> > _postponedEvents;
		static std::map<Interpreter*, Resubmitter*> _instances;
		static tthread::recursive_mutex _accessLock;

	};
};

#ifdef BUILD_AS_PLUGINS
PLUMA_INHERIT_PROVIDER(PostponeElement, Element);
#endif

}

#endif /* end of include guard: POSTPONEELEMENT_H_WN8EIYYI */
