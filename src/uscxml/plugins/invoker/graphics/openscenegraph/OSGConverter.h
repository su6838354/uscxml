#ifndef OSGCONVERTER_H_W09J90F0
#define OSGCONVERTER_H_W09J90F0

#include <uscxml/Interpreter.h>
#include <osg/Node>
#include <osgViewer/ViewerEventHandlers>

#ifdef BUILD_AS_PLUGINS
#include "uscxml/plugins/Plugins.h"
#endif

namespace uscxml {

class OSGConverter : public InvokerImpl {
public:
	OSGConverter();
	virtual ~OSGConverter();
	virtual boost::shared_ptr<IOProcessorImpl> create(Interpreter* interpreter);

	virtual std::set<std::string> getNames() {
		std::set<std::string> names;
		names.insert("osgconverter");
		names.insert("osgconvert");
		names.insert("http://uscxml.tk.informatik.tu-darmstadt.de/#osgconverter");
		names.insert("http://uscxml.tk.informatik.tu-darmstadt.de/#osgconvert");
		return names;
	}

	virtual Data getDataModelVariables();
	virtual void send(const SendRequest& req);
	virtual void cancel(const std::string sendId);
	virtual void invoke(const InvokeRequest& req);

	osg::Matrix requestToModelPose(const SendRequest& req);
	osg::Matrix requestToCamPose(const SendRequest& req);

	static osg::Matrix eulerToMatrix(double pitch, double roll, double yaw);
	static void matrixToEuler(const osg::Matrix& m, double& pitch, double& roll, double& yaw);

protected:
	class NameRespectingWriteToFile : public osgViewer::ScreenCaptureHandler::WriteToFile {
	public:
		NameRespectingWriteToFile(const std::string& filename,
		                          const std::string& extension,
		                          SavePolicy savePolicy) : osgViewer::ScreenCaptureHandler::WriteToFile(filename, extension, savePolicy) {
		}

		virtual void operator()(const osg::Image& image, const unsigned int context_id);
	};

	uscxml::concurrency::BlockingQueue<SendRequest> _workQueue;
	osg::ref_ptr<osg::Node> setupGraph(const std::string filename);

	std::map<std::string, std::pair<long, osg::ref_ptr<osg::Node> > > _models;
	tthread::recursive_mutex _cacheMutex;

	std::set<tthread::thread*> _threads;

	static void run(void*);
	void process(const SendRequest& req);

	bool _isRunning;
};

#ifdef BUILD_AS_PLUGINS
PLUMA_INHERIT_PROVIDER(OSGConverter, Invoker);
#endif

}


#endif /* end of include guard: OSGCONVERTER_H_W09J90F0 */
