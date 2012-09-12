/* $Id: T3Error.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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

/// @file T3Error.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'taxon3.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: T3Error_.hpp


#ifndef OBJECTS_TAXON3_T3ERROR_HPP
#define OBJECTS_TAXON3_T3ERROR_HPP

// Avoid a run-in with a Windows macro 
#ifdef GetMessage 
#undef GetMessage 
#endif

// generated includes
#include <objects/taxon3/T3Error_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class NCBI_TAXON3_EXPORT CT3Error : public CT3Error_Base
{
    typedef CT3Error_Base Tparent;
public:
    // constructor
    CT3Error(void);
    // destructor
    ~CT3Error(void);

private:
    // Prohibit copy constructor and assignment operator
    CT3Error(const CT3Error& value);
    CT3Error& operator=(const CT3Error& value);

};

/////////////////// CT3Error inline methods

// constructor
inline
CT3Error::CT3Error(void)
{
}


/////////////////// end of CT3Error inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // OBJECTS_TAXON3_T3ERROR_HPP
/* Original file checksum: lines: 86, chars: 2372, CRC32: 3675b973 */
