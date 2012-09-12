/* $Id: T3Data.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 */

/// @file T3Data.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'taxon3.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: T3Data_.hpp


#ifndef OBJECTS_TAXON3_T3DATA_HPP
#define OBJECTS_TAXON3_T3DATA_HPP


// generated includes
#include <objects/taxon3/T3Data_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class NCBI_TAXON3_EXPORT CT3Data : public CT3Data_Base
{
    typedef CT3Data_Base Tparent;
public:
    // constructor
    CT3Data(void);
    // destructor
    ~CT3Data(void);

    void GetTaxFlags (bool& is_species_level, bool& force_consult, bool& has_nucleomorphs) const;

private:
    // Prohibit copy constructor and assignment operator
    CT3Data(const CT3Data& value);
    CT3Data& operator=(const CT3Data& value);

};

/////////////////// CT3Data inline methods

// constructor
inline
CT3Data::CT3Data(void)
{
}


/////////////////// end of CT3Data inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // OBJECTS_TAXON3_T3DATA_HPP
/* Original file checksum: lines: 86, chars: 2353, CRC32: a5f1b881 */
