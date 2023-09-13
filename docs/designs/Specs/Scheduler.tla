(* Scheduler Specification is a Non-Interleaving Specification. *)
---- MODULE Scheduler ----------------------------------------------------------
EXTENDS Sequences
VARIABLES p_seq,
          p_seq_maxlen,
          ctl,
          protoctl,
          progin,
          exin,
          exout,
          schdata
CONSTANTS Resource,
          CMD,
          Serializable,
          Content


Program == [Requirement: Resource, Command: Seq(CMD)]
ProgChan == INSTANCE Channel WITH Data <- Program, chan <- progin

Proto == INSTANCE SchProto WITH
            MsgContent <- Content,
            inchan <- exin,
            outchan <- exout,
            ctl <- protoctl,
            data <- schdata

(* Request from environment this step will*)
(* append the request to sequence *)
ProgReq(prog) == /\ ProgChan!Rcv (* Assert that pq is not full *)
                 /\ Len(p_seq) # p_seq_maxlen
                 /\ p_seq' = Append(p_seq, progin.val) (* Update status of pq *)

ResCheck == Proto!ResQueryReq

(* (\* Select ExecuteGroup to run program *\) *)
(* (\* from the head of Sequence pq *\) *)
Select == /\ Proto!ResQueryRep
          /\ LET current == Head(progin)
                (*Check Resource requirement*)
             IN /\ \E f \in [Content -> Resource]: current.Requirement = f[schdata]

================================================================================
