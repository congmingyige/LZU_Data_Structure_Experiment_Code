1. Integrated Ticketing System for City Bus and Subway
	Role: Ticket & Finance Center

2. Movie recommendation system (category, rating, mood, ...) with top 100+ movies you collected.
	Move: Collect from web

3. Motto poping system (provided with Bing mottoes)
	
4. Character coding among English, Simplified Chinese, and Traditional Chinese
	UTF8 <-> UTF16 <-> GB2312 <-> UniCode <-> <BIG5>

5. Tree like data program understanding
	Figure demo / list level, roots, and leaves
///////////////////////////////////////////////////////////////////////////////////
(
select TT.term1_id,T1.name,TT.relationship_type_id,TT.term2_id
		,T2.name
	from HaoT_GO_assocdb_201509.dbo.term2term as TT
		,HaoT_GO_assocdb_201509.dbo.term as T1
		,HaoT_GO_assocdb_201509.dbo.term as T2
	where TT.term1_id=T1.id
		and TT.term2_id=T2.id
		and TT.relationship_type_id=1
		and T1.name='biological_process'
)
///////////////////////////////////////////////////////////////////////////////////
ID=1872	name=immune system process
///////////////////////////////////////////////////////////////////////////////////
with T2T as (
	select term1_id,relationship_type_id,term2_id
		from HaoT_GO_assocdb_201509.dbo.term2term
		where term1_id=1872 and relationship_type_id=1
	union all
	select TT.term1_id,TT.relationship_type_id,TT.term2_id from T2T
		inner join HaoT_GO_assocdb_201509.dbo.term2term as TT
		on T2T.term2_id=TT.term1_id
	where TT.relationship_type_id=1
)
select distinct T2T.term1_id,T1.name,T2T.relationship_type_id,T2T.term2_id
		,T2.name
	from T2T
		,HaoT_GO_assocdb_201509.dbo.term as T1
		,HaoT_GO_assocdb_201509.dbo.term as T2
	where T2T.term1_id=T1.id
		and T2T.term2_id=T2.id
		and T2T.relationship_type_id=1
///////////////////////////////////////////////////////////////////////////////////
(766 lines)


6. Data transfer of ACR20
	PMID	DrugName

7. Campus card for bus and canteen
	Move: Collect from web

8. power set construction for  C(26,13)
      (1 2 3)=> (( ) (2) (3) (2 3)  
                        (1) (1 2)  (1 3)  (1 2 3))
	Statistics & write to file & analysis

9. permutation 
>(permute '(1 2 3))
((1 2 3) (1 3 2)
 (2 1 3) (2 3 1)
 (3 1 2) (3 2 1))

10. Is artificial randome distribution real with time(0) in C <time.h>?

