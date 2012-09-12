/* $Id: Auth_list.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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

/// @Auth_list.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'biblio.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: Auth_list_.hpp


#ifndef OBJECTS_BIBLIO_AUTH_LIST_HPP
#define OBJECTS_BIBLIO_AUTH_LIST_HPP


// generated includes
#include <objects/biblio/Auth_list_.hpp>

#include <objects/biblio/citation_base.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class NCBI_BIBLIO_EXPORT CAuth_list
    : public CAuth_list_Base, public ICitationBase
{
    typedef CAuth_list_Base Tparent;
public:
    // constructor
    CAuth_list(void);
    // destructor
    ~CAuth_list(void);

    size_t GetNameCount(void) const;

protected:
    bool GetLabelV1(string* label, TLabelFlags flags) const;
    bool GetLabelV2(string* label, TLabelFlags flags) const;

private:
    // Prohibit copy constructor and assignment operator
    CAuth_list(const CAuth_list& value);
    CAuth_list& operator=(const CAuth_list& value);
};

/////////////////// CAuth_list inline methods

// constructor
inline
CAuth_list::CAuth_list(void)
{
}


/////////////////// end of CAuth_list inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // OBJECTS_BIBLIO_AUTH_LIST_HPP
/* Original file checksum: lines: 94, chars: 2572, CRC32: 9913f83c */
