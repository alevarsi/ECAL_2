#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/ESGetToken.h"

#include "CondFormats/DataRecord/interface/EcalLaserDbRecord.h"
#include "CondFormats/EcalObjects/interface/EcalLaserDbService.h"

class DumpEcalLaserCorrections : public edm::one::EDAnalyzer<> {
public:
  explicit DumpEcalLaserCorrections(const edm::ParameterSet&);
  ~DumpEcalLaserCorrections();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

  edm::ESGetToken<EcalLaserDbService, EcalLaserDbRecord> laserToken_;
};

DumpEcalLaserCorrections::DumpEcalLaserCorrections(const edm::ParameterSet& iConfig)
    : laserToken_(esConsumes<EcalLaserDbService, EcalLaserDbRecord>()) {}

DumpEcalLaserCorrections::~DumpEcalLaserCorrections() {}

void DumpEcalLaserCorrections::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  const auto& laserService = iSetup.getData(laserToken_);

  for (int i = 1; i <= 75848; ++i) {  // Numero totale di cristalli in EB e EE
    float laserCorrection = laserService.getLaserCorrection(i);
    edm::LogInfo("DumpEcalLaserCorrections") << "Crystal " << i << ": Laser Correction = " << laserCorrection;
  }
}

void DumpEcalLaserCorrections::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  descriptions.add("dumpEcalLaserCorrections", desc);
}

// Definisce il modulo come un plugin
DEFINE_FWK_MODULE(DumpEcalLaserCorrections);
