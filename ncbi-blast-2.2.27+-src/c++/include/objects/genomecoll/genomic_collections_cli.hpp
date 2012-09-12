/* $Id: genomic_collections_cli.hpp 371868 2012-08-13 15:10:25Z rafanovi $
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

/// @file genomic_collections_cli.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'gencoll_client.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: genomic_collections_cli_.hpp


#ifndef INTERNAL_GPIPE_OBJECTS_GENOMECOLL_GENOMIC_COLLECTIONS_CLI_HPP
#define INTERNAL_GPIPE_OBJECTS_GENOMECOLL_GENOMIC_COLLECTIONS_CLI_HPP


// generated includes
#include <objects/genomecoll/genomic_collections_cli_.hpp>
#include <objects/genomecoll/GCClient_AttributeFlags.hpp>
#include <objects/genomecoll/GCClient_GetAssemblyReques.hpp>
// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////////////////////////////////////////////////////////////////
class CGenomicCollectionsService : public CGenomicCollectionsService_Base
{
    typedef CGenomicCollectionsService_Base Tparent;
public:
    // constructor
    CGenomicCollectionsService(void);
    // destructor
    ~CGenomicCollectionsService(void);

    virtual void x_Connect();

    // Override this to supply your own URL.
    virtual string x_GetURL();

    typedef CGCClient_GetAssemblyRequest::ELevel ELevel;

    typedef EGCClient_AttributeFlags EAttributeFlags;

    CRef<CGC_Assembly> GetAssembly
        (string acc, 
         int level = CGCClient_GetAssemblyRequest::eLevel_scaffold,
         int asmAttrFlags = eGCClient_AttributeFlags_none, 
         int chrAttrFlags = eGCClient_AttributeFlags_biosource, 
         int scafAttrFlags = eGCClient_AttributeFlags_none, 
         int compAttrFlags = eGCClient_AttributeFlags_none);

    CRef<CGC_Assembly> GetAssembly
        (int releaseId, 
         int level = CGCClient_GetAssemblyRequest::eLevel_scaffold,
         int asmAttrFlags = eGCClient_AttributeFlags_none, 
         int chrAttrFlags = eGCClient_AttributeFlags_biosource, 
         int scafAttrFlags = eGCClient_AttributeFlags_none, 
         int compAttrFlags = eGCClient_AttributeFlags_none);


private:
    // Prohibit copy constructor and assignment operator
    CGenomicCollectionsService(const CGenomicCollectionsService& value);
    CGenomicCollectionsService& operator=(const CGenomicCollectionsService& value);

};

/////////////////// CGenomicCollectionsService inline methods

// constructor
inline
CGenomicCollectionsService::CGenomicCollectionsService(void)
{
}


/////////////////// end of CGenomicCollectionsService inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE


#endif // INTERNAL_GPIPE_OBJECTS_GENOMECOLL_GENOMIC_COLLECTIONS_CLI_HPP
/* Original file checksum: lines: 86, chars: 2754, CRC32: 2b52f173 */
