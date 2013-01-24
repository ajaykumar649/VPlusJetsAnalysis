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
  std::map<TString,std::vector<std::pair<double,double> > > systrates; /*  TString = systname
									   vector index over channels
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

  // Histogram manipulation
  static const double minimum_signal_content=0.01;

  Card(double         procchanyield,
       const TString& procname,
       const TString& systname,
       const TString& channame,
       const bool     issignal
       );

  void
    addProcessChannel(double         procchanyield,// process/channel yield
		      const TString& procname,     // process name 
		      const TString& systname,     // name of (shape) systematic applied
		      const int      ichanref,     // channel reference index
		      const int      ichan,        // channel index
		      const int      nchan,        // number of channels in card
		      const bool     issignal
		      );
  
  void
    addSystematic(const TString& systname,     // systematic name 
		  const TString& procname,     // process name 
		  int            ichan,        // channel index
		  double         uncval
		  );

  void
    addModelParam(const TString& paramname,
		  const TString& paramtype
		  );

  void
    addShapeFiles(const ShapeFiles_t& shapesfile) { shapespecs.push_back(shapesfile); }

  void
    Print(const TString& dcardname=""
	  );

 private:
  int nsigproc;
  int nbackproc;
  std::set<TString> channels;
  ProcData_t data;   // data is identified separately as "observation"
  std::vector<ShapeFiles_t> shapespecs;
  std::vector<ModelParam_t> modelparams;
  std::deque<ProcData_t> processes; // push_front for signal, push_back for background
  std::map<TString,int> pname2index;  // map from process name to the deque index in "processes"
  std::map<TString,TString> systematics; // name, pdf function
};
