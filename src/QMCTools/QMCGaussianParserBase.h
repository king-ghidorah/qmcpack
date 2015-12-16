#ifndef QMCPLUSPLUS_TOOLS_EXTERNAL_GAUSSIANPARSERBASE_H
#define QMCPLUSPLUS_TOOLS_EXTERNAL_GAUSSIANPARSERBASE_H
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include "OhmmsData/OhmmsElementBase.h"
#include "Utilities/SimpleParser.h"
#include "Particle/ParticleSet.h"

using namespace qmcplusplus;

struct QMCGaussianParserBase
{

  typedef double value_type;
  typedef ParticleSet::SingleParticlePos_t SingleParticlePos_t;

  bool multideterminant;
  bool BohrUnit;
  bool SpinRestricted;
  bool Periodicity;
  bool UseHDF5;
  bool zeroCI;
  bool orderByExcitation;
  bool addJastrow;
  bool addJastrow3Body;
  int IonChargeIndex;
  int ValenceChargeIndex;
  int AtomicNumberIndex;
  int NumberOfAtoms;
  int NumberOfEls;
  int SpinMultiplicity;
  int NumberOfAlpha, NumberOfBeta;
  int SizeOfBasisSet;
// mmorales: number of Molecular orbitals, not always equal to SizeOfBasisSet
  int numMO, readNO, readGuess, numMO2print;
// benali: Point Charge from FMO ESP 
  int *  ESPIonChargeIndex;
  int * ESPValenceChargeIndex;
  int * ESPAtomicNumberIndex;
  int TotNumMonomer;
  ParticleSet *ESPSystem;
  std::vector <vector<double> > ESP;
  std::vector <vector <string> > ESPGroupName;
  xmlNodePtr createESPSet(int iesp);
  static std::map<int,std::string> ESPName;
  int FMOIndexI,FMOIndexJ,FMOIndexK;
  bool FMO, FMO1,FMO2,FMO3;
  

  std::string Title;
  std::string basisType;
  std::string basisName;
  std::string Normalized;
  std::string CurrentCenter;
  std::string outputFile;
  std::string angular_type;

  ParticleSet IonSystem;


  std::vector<string> GroupName;

  std::vector<int> gShell, gNumber, gBound;
  std::vector<int> Occ_alpha, Occ_beta;
  std::vector<value_type> Qv;
  std::vector<value_type> gExp, gC0, gC1;
  std::vector<value_type> EigVal_alpha, EigVal_beta;
  std::vector<value_type> EigVec;
  //std::vector<GaussianCombo<value_type> > gExp, gC0, gC1;
  //std::string EigVecU, EigVecD;
  xmlNodePtr gridPtr;
  std::vector<std::string> CIalpha,CIbeta;
  std::vector<std::string> CSFocc;
  std::vector<vector<std::string> > CSFalpha,CSFbeta;
  std::vector<vector<double> > CSFexpansion;
  std::vector<double> CIcoeff;
  std::vector<int> CIexcitLVL;
  int ci_size,ci_nca,ci_ncb,ci_nea,ci_neb,ci_nstates;
  double ci_threshold;
  bool usingCSF;
  bool VSVB;

  std::vector<pair<int,double> > coeff2csf;

  QMCGaussianParserBase();
  QMCGaussianParserBase(int argc, char** argv);

  void setOccupationNumbers();

  void createGridNode(int argc, char** argv);

  void createSPOSets(xmlNodePtr,xmlNodePtr);
  xmlNodePtr createElectronSet();
  xmlNodePtr createIonSet();
  xmlNodePtr createBasisSet();
  xmlNodePtr createCenter(int iat, int _off);
  void createShell(int n, int ig, int off_, xmlNodePtr abasis);
  xmlNodePtr createDeterminantSet();
  xmlNodePtr createMultiDeterminantSet();
  xmlNodePtr createMultiDeterminantSetVSVB();
  xmlNodePtr createDeterminantSetWithHDF5();
  xmlNodePtr createJ3();
  xmlNodePtr createJ2();
  xmlNodePtr createJ1();


  int numberOfExcitationsCSF(string&);

  void map2GridFunctors(xmlNodePtr cur);
  virtual void parse(const std::string& fname) = 0;

  virtual void dump(const string& psi_tag,
                    const string& ion_tag);

  virtual void Fmodump(const string& psi_tag,
                                 const string& ion_tag,
                                 std::string Mytag);

  //static std::vector<std::string> IonName;
  static std::map<int,std::string> IonName;

  static std::vector<std::string> gShellType;
  static std::vector<int>         gShellID;

  static void init();
};
#endif
