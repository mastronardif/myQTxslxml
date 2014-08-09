<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Significant characters question updating -->
<!-- Import the identity transformation. -->

 <!--
   <xsl:import href="Identity.xsl"/>
  -->
   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>


    <!-- Mark question as deleted /ssn/p[@idx='27']/. -->


  <xsl:template match="ssn/p[@idx='6']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="concat('FM New',.)"/>
     </xsl:attribute>

    <xsl:attribute name="FM_newtagSIG">
     <xsl:value-of select="concat('FM New',.)"/>
   </xsl:attribute>

  </xsl:template>

  <xsl:template match="ssn/p[@idx='6']/respLs/respR/@*">
    <xsl:call-template name="XMLTOTITLE221" />
  </xsl:template>


 <xsl:template match="ssn/p[@idx='6']">
 <xsl:call-template name="makeSignificant01" />
 <!--
 <xsl:copy-of select="." />
<fu>
<xsl:copy-of select="." />
</fu>
-->
  </xsl:template>

<xsl:variable name="sigChars" select="23"/> <!-- <xsl:variable name="sigChars" select="%1"/>-->

<xsl:template name="makeSignificant01">

 <makeSignificant01>
    <Original><xsl:copy-of select="." /></Original>

<newshit>
<xsl:element name="{name(.)}">
    <xsl:for-each select="./@*">
    <xsl:choose>
        <xsl:when test="name(.) = 'sig'">
            <xsl:attribute name="{name(.)}"><xsl:value-of select="$sigChars"/></xsl:attribute>
        </xsl:when>

                            <xsl:otherwise>
                            <xsl:attribute name="{name(.)}">
                                <xsl:value-of select="."/>
                            </xsl:attribute>
                            </xsl:otherwise>
    </xsl:choose>
<!--
        <xsl:attribute name="{name(.)}">
            <xsl:value-of select="."/>
        </xsl:attribute>
        -->
    </xsl:for-each>

<!--
    <xsl:element name="Jack">
        <xsl:attribute name="you">
            <xsl:value-of select="'off'"/>
        </xsl:attribute>
    </xsl:element> -->

    <!-- for each element -->
    <xsl:for-each select="./*">

        <xsl:choose>
              <!-- <xsl:when test="@respLS">-->
              <xsl:when test="position()  = 92">
              <xsl:value-of select="position()" />
<SKIP/>
<xsl:value-of select="."/> <xsl:value-of select="name(.)"/><skip/>
              </xsl:when>

              <xsl:when test="name(.) = 'respLs'">
                    <!-- <ADDSOMEATTRIBUEST/> <xsl:copy-of select="." /> <goaheadAddSomeShit/> -->
   parent11
                <xsl:element name="{name(.)}"> <!-- respLs -->
                       <xsl:for-each select="./@*">

                            <xsl:attribute name="{name(.)}">
                                <xsl:value-of select="."/>
                            </xsl:attribute>
                        </xsl:for-each>

                        <!-- elements -->
                        <xsl:for-each select="./*">

                        <xsl:choose>

                            <xsl:when test="name(.) = 'respR'">
                               <!-- <xsl:copy-of select="." /> -->
                                <xsl:element name="{name(.)}">
                                    <!-- add new attrib or update -->

                                    <xsl:for-each select="./@*">
                                        <!-- <xsl:attribute name="{name(.)}">
                                        <xsl:value-of select="."/> </xsl:attribute> -->


<xsl:choose>
<xsl:when test="name(.) = 'respLS'">
<xsl:attribute name="{name(.)}"><xsl:value-of select="."/> </xsl:attribute>
<xsl:attribute name="sig_respLS"><xsl:value-of select="substring(.,1, $sigChars)"/> </xsl:attribute>


</xsl:when>
                            <xsl:otherwise> <!-- leave attributes unchanged -->
                               <xsl:copy-of select="." />
                               <xsl:attribute name="{name(.)}">
                               <xsl:value-of select="."/> </xsl:attribute>

                            </xsl:otherwise>
                        </xsl:choose>

                                    </xsl:for-each>

                               </xsl:element>

                            </xsl:when>


                            <!-- other elements ignore -->
                            <xsl:otherwise>
                               <xsl:copy-of select="." />
                            </xsl:otherwise>
                        </xsl:choose>

                        </xsl:for-each>

                    </xsl:element> <!-- /respLs -->

parent21
<!--
   <xsl:for-each select="./*">
        <xsl:copy-of select="." />
            <xsl:for-each select="./*">
                <xsl:copy-of select="." />
            </xsl:for-each>
   </xsl:for-each>
   -->
   FOR EACH ELEM
              </xsl:when>



              <xsl:when test="name(.) = 'v'">
   <ADDSOMEATTRIBUEST/> <xsl:copy-of select="." />

              </xsl:when>

                 <!-- Ignore other emlements -->
                 <xsl:otherwise>
                    <xsl:copy-of select="." />
                 </xsl:otherwise>
         </xsl:choose>


<!--
        bb <xsl:value-of select="position()" />
        <xsl:copy-of select="." />
        -->
    </xsl:for-each>

</xsl:element>
</newshit>
ZZZZZZZZZ

    <xsl:copy-of select="./respLs/respR" />

<xsl:value-of select="name(.)"/>

<xsl:element name="FUCK">
<xsl:attribute name="you">
 <xsl:value-of select="ass"/>
</xsl:attribute>
</xsl:element>

<!-- END -->

<xsl:element name="{name(.)}">
    <xsl:for-each select="./@*">

        <xsl:attribute name="{name(.)}">
            <xsl:value-of select="."/>
        </xsl:attribute>



    </xsl:for-each>

<!--
<xsl:element name="Jack">
    <xsl:attribute name="you">
    <xsl:value-of select="'off'"/>
    </xsl:attribute>
</xsl:element>
-->
</xsl:element>

<xsl:for-each select="./@*">

aa <xsl:value-of select="position()" />
 <xsl:value-of select="name(.)"/>=
<xsl:value-of select="." />

</xsl:for-each>

        <!-- <xsl:for-each select="./*"> -->
        <xsl:for-each select="./*">

bb <xsl:value-of select="position()" />
<xsl:copy-of select="." />
    </xsl:for-each>

</makeSignificant01>
</xsl:template>

<xsl:template match="ProductType">
<xsl:element name="{name()}">
 <xsl:apply-templates select="Features/Feature" />
</xsl:element>
</xsl:template>

<xsl:template match="Features/Feature">
<xsl:element name="{@Name}">
    <xsl:value-of select="text()" />
</xsl:element>
</xsl:template>


<xsl:template name="XMLTOTITLE221">

 <xsl:for-each select=".">

        <xsl:choose>
              <!-- <xsl:when test="@respLS">-->
              <xsl:when test="position()  = 2">
                    <xsl:attribute name="{name()}">
                     <xsl:value-of select="concat('FM33 New ',.)"/>
                   </xsl:attribute>

              </xsl:when>

                 <!-- default 3 identifier cols -->
                 <xsl:otherwise>
                 <xsl:attribute name="{name()}">
                  <xsl:value-of select="concat('FM22 New ',.)"/>
                </xsl:attribute>
                 </xsl:otherwise>
           </xsl:choose>

 <xsl:attribute name="{name()}">
  <xsl:value-of select="concat('FM New ',.)"/>
</xsl:attribute>
<!--
   <replace_respA>
   <xsl:attribute name="{name()}">
    <xsl:value-of select="concat('FM New',.)"/>
   </xsl:attribute>

   <xsl:attribute name="qn">
    <xsl:value-of select="concat('FM New',.)"/>
  </xsl:attribute>
 </replace_respA>

    <v><xsl:value-of select="concat('FM-',.)" /></v>
    <c>ZZZZ</c>
    <xsl:element name="{name()}">
    </xsl:element>
-->

<!--
  <xsl:template match="ssn/p[@idx='6']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="concat('FM New',.)"/>
     </xsl:attribute>

    <xsl:attribute name="FM_newtagSIG">
     <xsl:value-of select="concat('FM New',.)"/>
   </xsl:attribute>

  </xsl:template>
  -->

 </xsl:for-each>

</xsl:template>


  <xsl:template match="ssn/p[@idx='6999']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="concat('FM New',.)"/>
     </xsl:attribute>
  </xsl:template>

  <xsl:template match="ssn/p[@idx='76']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="'fm-Yq'"/>
     </xsl:attribute>
  </xsl:template>

<!-- if not there lets add the attrib -->

  <xsl:template match="@nm">
     <xsl:attribute name="n">
       <xsl:value-of select="concat('new',.)"/>
     </xsl:attribute>
  </xsl:template>
</xsl:stylesheet>
