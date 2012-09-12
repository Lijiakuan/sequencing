/* $Id: Seq_graph.cpp 371868 2012-08-13 15:10:25Z rafanovi $
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
 *   using the following specifications:
 *   'seqres.asn'.
 */

// standard includes
#include <ncbi_pch.hpp>

// generated includes
#include <objects/seqres/Seq_graph.hpp>

#include <serial/objhook.hpp>
#include <corelib/ncbi_param.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CSeq_graph::~CSeq_graph(void)
{
}


NCBI_PARAM_DECL(int, OBJECTS, SEQ_GRAPH_RESERVE);
NCBI_PARAM_DEF_EX(int, OBJECTS, SEQ_GRAPH_RESERVE, 1,
                  eParam_NoThread, OBJECTS_SEQ_GRAPH_RESERVE);
static NCBI_PARAM_TYPE(OBJECTS, SEQ_GRAPH_RESERVE) s_Reserve;

void CSeq_graph::CReserveHook::PreReadChoiceVariant(
    CObjectIStream& in,
    const CObjectInfoCV& variant)
{
    if ( !s_Reserve.Get() ) {
        return;
    }
    if ( CSeq_graph* graph = CType<CSeq_graph>::GetParent(in) ) {
        size_t size = graph->GetNumval();
        switch ( variant.GetVariantIndex() ) {
        case C_Graph::e_Real:
            graph->SetGraph().SetReal().SetValues().reserve(size);
            break;
        case C_Graph::e_Int:
            graph->SetGraph().SetInt().SetValues().reserve(size);
            break;
        case C_Graph::e_Byte:
            graph->SetGraph().SetByte().SetValues().reserve(size);
            break;
        default:
            break;
        }
    }
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE
