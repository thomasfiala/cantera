#ifndef CT_REFINE_H
#define CT_REFINE_H

namespace Cantera {

    class Domain1D;

    class Refiner {

    public:

        Refiner(Domain1D& domain);
        virtual ~Refiner(){}

        void setCriteria(doublereal ratio = 10.0,
            doublereal slope = 0.8, 
            doublereal curve = 0.8) {
            m_ratio = ratio; m_slope = slope; m_curve = curve;
        }
        void setActive(int comp, bool state = true) { m_active[comp] = state; }
        void setMaxPoints(int npmax) { m_npmax = npmax; }
        int analyze(int n, const doublereal* z, const doublereal* x);
        int getNewGrid(int n, const doublereal* z, int nn, doublereal* znew);
        //int getNewSoln(int n, const doublereal* x, doublereal* xnew);
        int nNewPoints() { return m_loc.size(); }
        void show();
        bool newPointNeeded(int j) { 
            return m_loc.find(j) != m_loc.end();
        }
        bool keepPoint(int j) { 
            return m_keep.find(j) != m_keep.end();
        }
        double value(const double* x, int i, int j);

    protected:

        map<int, int>       m_loc;
        map<int, int>       m_keep;
        map<string, int>    m_c;
        vector<bool>        m_active;
        doublereal          m_ratio, m_slope, m_curve;
        doublereal          m_min_range;
        Domain1D*            m_domain;
        int                 m_nv, m_npmax;
        doublereal          m_thresh;

    };

}

#endif
