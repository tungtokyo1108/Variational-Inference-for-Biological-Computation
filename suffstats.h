
/********************

Adopted PhyloBayes MPI. https://github.com/bayesiancook/pbmpi
Lartillot, N., Rodrigue, N., Stubbs, D. & Richer, J. 
PhyloBayes MPI: Phylogenetic reconstruction with infinite mixtures of profiles in a parallel environment. Syst. Biol. 62, 611–615 (2013).

**********************/


void UpdateSiteRateSuffStat() = 0;
// gathers site-specific suff stats for updating site-specific rates
// declared in RateProcess
// are always of the exponential type:
// suff stat lkelihood ~ r^{count} exp(-beta r)
// where count and beta are the 2 suffstats (integer and double)

void UpdateBranchLengthSuffStat() = 0;
// gathers branch-specific suff stats for updating branch lengths
// declared in BranchProcess
// are always of the exponential type:
// suff stat lkelihood ~ l^{count} exp(-beta l)
// where count and beta are the 2 suffstats (integer and double)

void UpdateSiteProfileSuffStat() = 0;
// gather site-specific suff stats for updating all parameters of the substitution process(es)
// declared in ProfileProcess
// can be of different types, either exponential, or general

// general site-specific profile suff stats:
// - state at the root for that site
// - total amount of time (*rate) in each state across the tree for that site
// - total number of substitutions between each pair of states across the tree for that site

// all these functions are implemented in PhyloProcess specialized classes
// (but this calls functions of SubstitutionProcess specialized versions, and functions of BranchSitePath)

// based on these 3 fundamental suff stat collecting functions,
// accessory functions are defined, for collecting and pooling site-specific suffstats in various ways
// depending on which parameters need to be updated (and for which the likelihood needs to be quickly recomputed)

// e.g.

//
// in DGamRateProcess
//
// collecting statistics for each discrete category
void UpdateRateSuffStat();

// computing the loglikelihood based on sufficient statistics
double RateSuffStatLogProb();

//
// in DPProcesses:
//

// collecting statistics for each component of the mixture
void UpdateModeProfileSuffStat();
void UpdateModeProfileSuffStat(int cat);


// computing the loglikelihood based on sufficient statistics
double ProfileSuffStatLogProb();
// for one component in particular
double ProfileSuffStatLogProb(int cat);
// for one particular site when allocated to one particular component
double LogStatProb(int site, int cat);


