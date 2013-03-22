#include <set>
#include <vector>
#include <map>
#include <deque>
#include "TString.h"

struct ProcData_t {
  ProcData_t() : name(""),procindex(-1) {}
  TString name;
  int procindex;                                             // index to be put into the datacard!
  std::map<TString,double> channels;
  std::map<TString,std::pair<double,double> > systrates; /*  TString = systname+channame
							     pair of doubles for two-sided errors
							     first = DOWN, second = UP
							 */
};

struct ShapeFiles_t {
  ShapeFiles_t(const TString& inproc,
	       const TString& inchan,
	       const TString& infile,
	       const TString& inhist,
	       const TString& inhistwithsyst="") :
    process(inproc),channel(inchan),file(infile),histo(inhist),histo_with_syst(inhistwithsyst) {}
  TString process;
  TString channel;
  TString file;
  TString histo;
  TString histo_with_syst;
};

struct ModelParam_t {
  TString name;
  TString type;
};

class Card {
 public:

  Card(double         procchanyield,
       const TString& procname,
       const TString& systname,
       const TString& channame,
       const bool     issignal
       );

  void
    addProcessChannel(double         procchanyield,// process/channel yield
		      const TString& procname,     // process name 
		      const TString& channame,     // name of channel
		      const TString& systname,     // name of (shape) systematic applied
		      const bool     issignal
		      );
  
  void
    addSystematic(const TString& systname,     // systematic name 
		  const TString& procname,     // process name 
		  const TString& channame,     // name of channel
		  double         uncval
		  );

  void
    addModelParam(const TString& paramname,
		  const TString& paramtype
		  );

  void
    addShapeFiles(const ShapeFiles_t& shapesfile) { shapespecs_.push_back(shapesfile); }

  void
    addSyst2ShapeFile(const TString& procname,
		      const TString& systname);

  void
    Print(const TString& dcardname=""
	  );

 private:
  int nsigproc_;
  int nbackproc_;
  ProcData_t data_;   // data is identified separately as "observation"
  std::vector<ShapeFiles_t> shapespecs_;
  std::vector<ModelParam_t> modelparams_;
  std::deque<ProcData_t> processes_; // push_front for signal, push_back for background
  std::map<TString,int> pname2index_;  // map from process name to the deque index in "processes"
  std::map<TString,TString> systematics_; // name, pdf function
};
