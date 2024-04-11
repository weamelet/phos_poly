#include "PhosPoly.h"

PhosPolyStatus poly_int(int pow, void *dat, PhosPoly *pol) {
    pol->pow = pow;
    pol->dat = dat;
    pol->bas = &PhosBaseInt;
    return PhosPolyStatusOk;
};

PhosPolyStatus poly_flt(int pow, void *dat, PhosPoly *pol) {
    pol->pow = pow;
    pol->dat = dat;
    pol->bas = &PhosBaseFlt;
    return PhosPolyStatusOk;
};

PhosPolyStatus clc(PhosPoly *pol, void *opa, void **res) {    
    int len = pol->bas->len;
    void *resm = malloc(len);
    void *resd = *res;
    pol->bas->nul(&resd);
    for (int pos = 0; pos <= pol->pow; pos++) {
        pol->bas->get(pol->dat, pos, &resm);
        for (int i = 0; i < pos; i++)
            pol->bas->mul(opa, resm, &resm);
        pol->bas->sum(resd, resm, &resd);
    }
    return PhosPolyStatusOk;
};

PhosPolyStatus sum(PhosPoly *pol, PhosPoly *pom, PhosPoly *res) {
    if (pol->bas != pom->bas)
        return PhosPolyStatusError;
    int pown = pom->pow;
    if (pol->pow > pom->pow)
        pown = pol->pow;
    void *resl = malloc(pol->bas->len), *resm = malloc(pol->bas->len);
    void *ress = malloc(pol->bas->len);
    res->pow = pown;
    res->dat = malloc((pown + 1) * pol->bas->len);
    res->bas = pol->bas;
    for (int pos = 0; pos <= pown; pos++) {
        if (pos <= pol->pow && pos <= pom->pow) {
            res->bas->get(pol->dat, pos, &resl);
            res->bas->get(pom->dat, pos, &resm);
        } else if (pos <= pol->pow) {
            res->bas->get(pol->dat, pos, &resl);
            res->bas->nul(&resm);
        } else {
            res->bas->nul(&resl);
            res->bas->get(pom->dat, pos, &resm);
        }
        res->bas->sum(resl, resm, &ress);
        res->bas->set(ress, pos, &res->dat);
    }
    return PhosPolyStatusOk;
};

PhosPolyStatus scl(PhosPoly *pol, void *opa, PhosPoly *res) {
    res->pow = pol->pow;
    res->dat = malloc((pol->pow + 1) * pol->bas->len);
    res->bas = pol->bas;
    void *resm = malloc(pol->bas->len);
    for (int pos = 0; pos <= pol->pow; pos++) {
        pol->bas->get(pol->dat, pos, &resm);
        pol->bas->mul(resm, opa, &resm);
        pol->bas->set(resm, pos, &res->dat);
    }
    return PhosPolyStatusOk;
};

PhosPolyStatus mul(PhosPoly *pol, PhosPoly *pom, PhosPoly *res) {
    if (pol->bas != pom->bas)
        return PhosPolyStatusError;
    res->pow = (pol->pow + pom->pow);
    res->dat = malloc((pol->pow + pom->pow + 1) * pol->bas->len);
    res->bas = pol->bas;
    void *resl = malloc(pol->bas->len), *resm = malloc(pol->bas->len);
    void *ress = malloc(pol->bas->len);
    for (int pos1 = 0; pos1 <= pol->pow; pos1++)
        for (int pos2 = 0; pos2 <= pom->pow; pos2++) {
            pol->bas->get(pol->dat, pos1, &resl);
            pol->bas->get(pom->dat, pos2, &resm);
            pol->bas->mul(resl, resm, &ress);
            pol->bas->get(res->dat, pos1 + pos2, &resl);
            pol->bas->sum(resl, ress, &ress);
            pol->bas->set(ress, pos1 + pos2, &res->dat);
        }
    return PhosPolyStatusOk;
};

PhosPolyStatus com(PhosPoly *pol, PhosPoly *pom, PhosPoly *res) {
    if (pol->bas != pom->bas)
        return PhosPolyStatusError;
    res->pow = (pol->pow * pom->pow);
    res->dat = malloc((pol->pow * pom->pow + 1) * pol->bas->len);
    res->bas = pol->bas;
    void *ress = malloc(pol->bas->len);
    for (int pos = 0; pos <= pol->pow; pos++) {
        if (pos == 0) {
            pol->bas->set(pol->dat, 0, &res->dat);
        } else {
            PhosPoly *pod = pom;
            PhosPoly *podm = malloc (sizeof(PhosPoly));
            PhosPoly *pods = malloc (sizeof(PhosPoly));
            for (int pot = pos; pot > 1; pot--) {
                PhosPolyActions.mul(pod, pom, podm);
                pod = podm;
                podm = malloc (sizeof(PhosPoly));
            }
            pol->bas->get(pol->dat, pos, &ress);
            PhosPolyActions.scl(pod, ress, pods);
            pod = pods;
            PhosPolyActions.sum(res, pod, podm);
            *res = *podm;
        }
    }
    return PhosPolyStatusOk;
};

const PhosPolyActionsLibrary PhosPolyActions = {
    .clc = clc,
    .sum = sum,
    .scl = scl,
    .mul = mul,
    .com = com
};
