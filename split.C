using namespace ROOT; // RDataFrame's namespace

void split()
{
  RDataFrame df ("evetree", "RPCv4t_evtraw-20181218_082256.rre");
  TFile *f = TFile::Open("RPCv4t_evtraw-20181218_082256.rre");
  TTree *t1 = (TTree*)f->Get("evetree");
  cout<<"Number of entries = "<<t1->GetEntries()<<endl;

  int splitLevel = 10000;

  for(int ij=0; (((ij+1)*splitLevel)-1)<t1->GetEntries(); ij++) {
    char fileName[200];
    TString rootName = TString::Format("RPCv4t_evtraw-20181218_082256_%i.rre",ij);
    cout<<"Start="<<ij*splitLevel<<"\tEnd="<<(((ij+1)*splitLevel))-1<<endl;
    df.Range(ij*splitLevel, (((ij+1)*splitLevel))-1).Snapshot("evetree",std::string_view(rootName));
  }
}
