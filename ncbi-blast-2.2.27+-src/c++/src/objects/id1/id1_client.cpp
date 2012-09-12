/* $Id: id1_client.cpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 * Author:  Aaron Ucko, NCBI
 *
 * File Description:
 *   ID1 network client
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using specifications from the data definition file
 *   'id1.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>
#include <objects/id1/id1_client.hpp>
#include <objects/seqset/Seq_entry.hpp>
#include <objects/seqloc/Seq_id.hpp>
#include <serial/exception.hpp>

#include <objects/id1/ID1server_maxcomplex.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

void CID1Client::Ask(const CID1Client::TRequest& request,
                     CID1Client::TReply& reply,
                     CID1Client::TReplyChoice::E_Choice wanted)
{
    Ask(request, reply);
    if (reply.Which() == wanted) {
        return; // ok
    } else if (reply.IsError()) {
        NCBI_THROW(CException, eUnknown,
                   "CID1Client: server error: " + reply.GetErrorString());
    } else {
        reply.ThrowInvalidSelection(wanted);
    }
}

CRef<CSeq_entry> CID1Client::AskGetsefromgi(const CID1server_maxcomplex& req,
                                            CID1Client::TReply* reply)
{
    TReply reply0;
    if ( !reply ) {
        reply = &reply0;
    }
    try {
        return Tparent::AskGetsefromgi(req, reply);
    } catch (CInvalidChoiceSelection&) {
        if (m_AllowDeadEntries  &&  reply->IsGotdeadseqentry()) {
            return CRef<CSeq_entry>(&reply->SetGotdeadseqentry());
        } else {
            throw;
        }
    }
}


CRef<CSeq_entry> CID1Client::FetchEntry(int gi, int max_complexity)
{
    CRef<CID1server_maxcomplex> mc(new CID1server_maxcomplex);
    mc->SetGi(gi);
    mc->SetMaxplex(max_complexity);
    return AskGetsefromgi(*mc);
}


CRef<CSeq_entry> CID1Client::FetchEntry(const CSeq_id& id, int max_complexity)
{
    int gi = AskGetgi(id);
    if (gi == 0) {
        return CRef<CSeq_entry>();
    }
    return FetchEntry(gi, max_complexity);
}


CRef<CSeq_entry> CID1Client::FetchEntry(const string& id_string,
                                        int max_complexity)
{
    CSeq_id id(id_string);
    return FetchEntry(id, max_complexity);
}


// destructor
CID1Client::~CID1Client(void)
{
}

END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 64, chars: 1872, CRC32: cedfdc3e */
