/* $Id: TMgr_DisplayTrackRequest.hpp 371635 2012-08-09 17:42:05Z clausen $
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

/// @file TMgr_DisplayTrackRequest.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'trackmgr.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: TMgr_DisplayTrackRequest_.hpp


#ifndef INTERNAL_TRACKMGR_OBJECTS_TRACKMGR_TMGR_DISPLAYTRACKREQUEST_HPP
#define INTERNAL_TRACKMGR_OBJECTS_TRACKMGR_TMGR_DISPLAYTRACKREQUEST_HPP


// generated includes
#include <objects/trackmgr/TMgr_DisplayTrackRequest_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class NCBI_TRACKMGR_EXPORT CTMgr_DisplayTrackRequest :
    public CTMgr_DisplayTrackRequest_Base
{
    typedef CTMgr_DisplayTrackRequest_Base Tparent;
public:
    // constructor
    CTMgr_DisplayTrackRequest(void);
    // destructor
    ~CTMgr_DisplayTrackRequest(void);

    void SetClientName(const string&);
    void SetResourceName(const string&);
    void AddAssemblyAcc(const string&);
    void AddAssemblyNameTax(const string&, int);

private:
    // Prohibit copy constructor and assignment operator
    CTMgr_DisplayTrackRequest(const CTMgr_DisplayTrackRequest& value);
    CTMgr_DisplayTrackRequest& operator=(
        const CTMgr_DisplayTrackRequest& value);

};

/////////////////// CTMgr_DisplayTrackRequest inline methods

// constructor
inline
CTMgr_DisplayTrackRequest::CTMgr_DisplayTrackRequest(void)
{
}


/////////////////// end of CTMgr_DisplayTrackRequest inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // INTERNAL_TRACKMGR_OBJECTS_TRACKMGR_TMGR_DISPLAYTRACKREQUEST_HPP
/* Original file checksum: lines: 86, chars: 2779, CRC32: ef2e42ca */