/*#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CondFormats/EcalObjects/interface/EcalLaserAPDPNRatios.h"
#include "CondFormats/DataRecord/interface/EcalLaserAPDPNRatiosRcd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

class DumpEcalLaserCorrections : public edm::one::EDAnalyzer<> {
public:
  explicit DumpEcalLaserCorrections(const edm::ParameterSet&);
  ~DumpEcalLaserCorrections() override = default;

  void analyze(const edm::Event&, const edm::EventSetup&) override;

private:
  edm::EDGetTokenT<EcalRecHitCollection> eeRecHitToken_;
};

DumpEcalLaserCorrections::DumpEcalLaserCorrections(const edm::ParameterSet& iConfig)
  : eeRecHitToken_(consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("eeRecHits"))) {
}

void DumpEcalLaserCorrections::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<EcalRecHitCollection> eeRecHits;
  iEvent.getByToken(eeRecHitToken_, eeRecHits);

  edm::ESHandle<EcalLaserAPDPNRatios> laserRatios;
  iSetup.get<EcalLaserAPDPNRatiosRcd>().get(laserRatios);

  const auto& ratiosMap = laserRatios->getLaserRatiosMap();

  for (const auto& hit : *eeRecHits) {
    EEDetId detId = hit.detid();

    auto it = ratiosMap.find(detId);
    if (it != ratiosMap.end()) {
      edm::LogInfo("DumpEcalLaserCorrections")
        << "Laser APD/Pn ratio for crystal " << detId.rawId()
        << " in EE: " << it->second;
    } else {
      edm::LogWarning("DumpEcalLaserCorrections")
        << "No laser APD/Pn ratio found for crystal " << detId.rawId() << " in EE.";
    }
  }
}

DEFINE_FWK_MODULE(DumpEcalLaserCorrections);
*/