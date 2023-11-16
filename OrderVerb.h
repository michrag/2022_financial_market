#ifndef ORDERVERB_H_
#define ORDERVERB_H_

/**
 The Verb of an Order. It can be either BUY or SELL
 */
enum OrderVerb
{
    /** The order is used to Buy a given product */
    BUY,
    /** The order is used to Sell a given product */
    SELL
};

#endif //ORDERVERB_H_
