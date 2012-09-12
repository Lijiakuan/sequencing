/* $Id: Int_fuzz.hpp 371868 2012-08-13 15:10:25Z rafanovi $
 * ===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 * Author:  .......
 *
 * File Description:
 *   .......
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using specifications from the ASN data definition file
 *   'general.asn'.
 *
 * ===========================================================================
 */

#ifndef OBJECTS_GENERAL_INT_FUZZ_HPP
#define OBJECTS_GENERAL_INT_FUZZ_HPP


// generated includes
#include <objects/general/Int_fuzz_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// Forward declarations
class NCBI_GENERAL_EXPORT CInt_fuzz : public CInt_fuzz_Base
{
    typedef CInt_fuzz_Base Tparent;
public:
    // constructor
    CInt_fuzz(void);
    // destructor
    ~CInt_fuzz(void);

    void GetLabel(string* label, TSeqPos pos, bool right = true) const;

    /// n1 and n2 are the targets of the fuzz
    void AssignTranslated(const CInt_fuzz& f2, TSeqPos n1, TSeqPos n2);

    enum ECombine {
        /// go for the largest possible range
        eAmplify,
        /// go for the smallest range that allows each value
        /// individually to vary freely as long as the other balances
        /// it out to the extent possible
        eReduce
    };

    // Manipulators; n1 and n2 are the targets of the fuzz.
    // Adding anything to its negation (subtracting it from itself)
    // in eReduce mode should always yield zero.
    void Add     (const CInt_fuzz& f2, TSeqPos& n1, TSeqPos n2,
                  ECombine mode = eAmplify);
    void Subtract(const CInt_fuzz& f2, TSeqPos& n1, TSeqPos n2,
                  ECombine mode = eReduce);
    void Negate  (TSeqPos n);

    CRef<CInt_fuzz> Negative(TSeqPos n) const;

private:
    // Prohibit copy constructor and assignment operator
    CInt_fuzz(const CInt_fuzz& value);
    CInt_fuzz& operator=(const CInt_fuzz& value);

};



/////////////////// CInt_fuzz inline methods

// constructor
inline
CInt_fuzz::CInt_fuzz(void)
{
}


inline
CRef<CInt_fuzz> CInt_fuzz::Negative(TSeqPos n) const
{
    CRef<CInt_fuzz> result(new CInt_fuzz);
    result->Assign(*this);
    result->Negate(n);
    return result;
}


inline
void CInt_fuzz::Subtract(const CInt_fuzz& f2, TSeqPos& n1, TSeqPos n2,
                         ECombine mode)
{
    CRef<CInt_fuzz> neg(f2.Negative(n2));
    Add(*neg, n1, n2, mode);
}


/////////////////// end of CInt_fuzz inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // OBJECTS_GENERAL_INT_FUZZ_HPP
/* Original file checksum: lines: 90, chars: 2388, CRC32: e4127209 */
